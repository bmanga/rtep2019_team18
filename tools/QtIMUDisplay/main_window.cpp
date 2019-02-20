#include "main_window.h"
#include <QCheckBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSplineSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "chart.h"

MainWindow::MainWindow() : m_chartAccel(new Chart()), m_chartGyro(new Chart())
{
  m_chartAccel->setTitle("Acceleration data chart");
  m_chartAccel->legend()->hide();
  m_chartGyro->setTitle("Gyroscope data chart");
  m_chartGyro->legend()->hide();

  // Check boxes
  QCheckBox *Box1 = new QCheckBox("Axis X", this);
  Box1->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartAccel->m_series_x,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartGyro->m_series_x,
                   &QAbstractSeries::setVisible);

  QCheckBox *Box2 = new QCheckBox("Axis Y", this);
  Box2->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartAccel->m_series_y,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartGyro->m_series_y,
                   &QAbstractSeries::setVisible);

  QCheckBox *Box3 = new QCheckBox("Axis Z");
  Box3->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartAccel->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartGyro->m_series_z,
                   &QAbstractSeries::setVisible);

  // Connect interface
  m_connectURI = new QLineEdit(this);
  m_connectButton = new QPushButton("connect", this);
  QHBoxLayout *connectInterfaceLayout = new QHBoxLayout(this);
  connectInterfaceLayout->addWidget(m_connectURI);
  connectInterfaceLayout->addWidget(m_connectButton);

  connect(m_connectButton, &QPushButton::clicked, this,
          &MainWindow::onConnectClicked);

  // Charts
  QChartView *chartView_1 = new QChartView(m_chartAccel, this);
  QChartView *chartView_2 = new QChartView(m_chartGyro, this);
  chartView_1->setRenderHint(QPainter::Antialiasing);
  chartView_2->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(connectInterfaceLayout);
  layout->addWidget(chartView_1);
  layout->addWidget(chartView_2);
  layout->addWidget(Box1);
  layout->addWidget(Box2);
  layout->addWidget(Box3);
  QWidget *charts = new QWidget(this);

  charts->setLayout(layout);
  setCentralWidget(charts);

  m_client.set_message_handler(
      [this](const void *data, long len) { this->on_message(data, len); });
}

MainWindow::~MainWindow()
{
  delete m_chartAccel;
  delete m_chartGyro;
}

struct sensors_data {
  float ax, ay, az;
  float gx, gy, gz;
};

void MainWindow::on_message(const void *d, long len)
{
  sensors_data data;
  memcpy(&data, d, len);
  auto x = std::chrono::system_clock::now() - m_time_start;
  double x_sec =
      std::chrono::duration_cast<std::chrono::milliseconds>(x).count() / 1000.0;

  m_chartAccel->m_series_x->append(x_sec, data.ax);
  m_chartAccel->m_series_y->append(x_sec, data.ay);
  m_chartAccel->m_series_z->append(x_sec, data.az);

  m_chartGyro->m_series_x->append(x_sec, data.gx);
  m_chartGyro->m_series_y->append(x_sec, data.gy);
  m_chartGyro->m_series_z->append(x_sec, data.gz);
  if (x_sec >= m_chartAccel->getXAxisMax()) {
    m_chartAccel->axisX()->setRange(x_sec - 10, x_sec);
    m_chartGyro->axisX()->setRange(x_sec - 10, x_sec);
  }
}

void MainWindow::onConnectClicked()
{
  m_time_start = std::chrono::system_clock::now();
  QString uri = m_connectURI->text();
  if (uri == "")
    return;
  m_client.connect_to(uri.toStdString());
  m_client.run_on_thread();
  m_connectButton->setText("disconnect");
  disconnect(m_connectButton, &QPushButton::clicked, this,
             &MainWindow::onConnectClicked);
  connect(m_connectButton, &QPushButton::clicked, this,
          &MainWindow::onDisconnectClicked);
}

void MainWindow::onDisconnectClicked()
{
  m_connectButton->setText("connect");
  disconnect(m_connectButton, &QPushButton::clicked, this,
             &MainWindow::onDisconnectClicked);
  connect(m_connectButton, &QPushButton::clicked, this,
          &MainWindow::onConnectClicked);
}
