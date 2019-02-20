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

MainWindow::MainWindow()
    : m_chartAccel_1(new Chart()),
      m_chartGyro_1(new Chart()),
      m_chartAccel_2(new Chart()),
      m_chartGyro_2(new Chart()),
      m_chartAccel_3(new Chart()),
      m_chartGyro_3(new Chart())
{
  m_chartAccel_1->setTitle("Acceleration data chart 1");
  m_chartAccel_1->legend()->hide();
  m_chartGyro_1->setTitle("Gyroscope data chart 1");
  m_chartGyro_1->legend()->hide();

  m_chartAccel_2->setTitle("Acceleration data chart 2");
  m_chartAccel_2->legend()->hide();
  m_chartGyro_2->setTitle("Gyroscope data chart 2");
  m_chartGyro_2->legend()->hide();

  m_chartAccel_3->setTitle("Acceleration data chart 3");
  m_chartAccel_3->legend()->hide();
  m_chartGyro_3->setTitle("Gyroscope data chart 3");
  m_chartGyro_3->legend()->hide();

  // Check boxes
  QCheckBox *Box1 = new QCheckBox("Axis X", this);
  Box1->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartAccel_1->m_series_x,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartGyro_1->m_series_x,
                   &QAbstractSeries::setVisible);

  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartAccel_2->m_series_x,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartGyro_2->m_series_x,
                   &QAbstractSeries::setVisible);

  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartAccel_3->m_series_x,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box1, &QCheckBox::stateChanged, m_chartGyro_3->m_series_x,
                   &QAbstractSeries::setVisible);

  QCheckBox *Box2 = new QCheckBox("Axis Y", this);
  Box2->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartAccel_1->m_series_y,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartGyro_1->m_series_y,
                   &QAbstractSeries::setVisible);

  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartAccel_2->m_series_y,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartGyro_2->m_series_y,
                   &QAbstractSeries::setVisible);

  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartAccel_3->m_series_y,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box2, &QCheckBox::stateChanged, m_chartGyro_3->m_series_y,
                   &QAbstractSeries::setVisible);

  QCheckBox *Box3 = new QCheckBox("Axis Z");
  Box3->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartAccel_1->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartGyro_1->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartAccel_2->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartGyro_2->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartAccel_3->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box3, &QCheckBox::stateChanged, m_chartGyro_3->m_series_z,
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
  QChartView *chartView_1 = new QChartView(m_chartAccel_1, this);
  QChartView *chartView_2 = new QChartView(m_chartGyro_1, this);
  QChartView *chartView_3 = new QChartView(m_chartAccel_2, this);
  QChartView *chartView_4 = new QChartView(m_chartGyro_2, this);
  QChartView *chartView_5 = new QChartView(m_chartAccel_3, this);
  QChartView *chartView_6 = new QChartView(m_chartGyro_3, this);

  chartView_1->setRenderHint(QPainter::Antialiasing);
  chartView_2->setRenderHint(QPainter::Antialiasing);
  chartView_3->setRenderHint(QPainter::Antialiasing);
  chartView_4->setRenderHint(QPainter::Antialiasing);
  chartView_5->setRenderHint(QPainter::Antialiasing);
  chartView_6->setRenderHint(QPainter::Antialiasing);

  QHBoxLayout *layout_graphs1 = new QHBoxLayout(this);
  layout_graphs1->addWidget(chartView_1);
  layout_graphs1->addWidget(chartView_2);
  QHBoxLayout *layout_graphs2 = new QHBoxLayout(this);
  layout_graphs2->addWidget(chartView_3);
  layout_graphs2->addWidget(chartView_4);
  QHBoxLayout *layout_graphs3 = new QHBoxLayout(this);
  layout_graphs3->addWidget(chartView_5);
  layout_graphs3->addWidget(chartView_6);

  QHBoxLayout *layout_boxes = new QHBoxLayout(this);
  layout_boxes->addWidget(Box1);
  layout_boxes->addWidget(Box2);
  layout_boxes->addWidget(Box3);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(connectInterfaceLayout);
  layout->addLayout(layout_graphs1);
  layout->addLayout(layout_graphs2);
  layout->addLayout(layout_graphs3);
  layout->addLayout(layout_boxes);

  QWidget *charts = new QWidget(this);

  charts->setLayout(layout);
  setCentralWidget(charts);

  m_client.set_message_handler(
      [this](const void *data, long len) { this->on_message(data, len); });
}

MainWindow::~MainWindow()
{
  delete m_chartAccel_1;
  delete m_chartGyro_1;
  delete m_chartAccel_2;
  delete m_chartGyro_2;
  delete m_chartAccel_3;
  delete m_chartGyro_3;
}

struct sensors_packet {
  float ax, ay, az;
  float gx, gy, gz;
};

struct sensors_data {
  sensors_packet p1, p2, p3;
};

void MainWindow::on_message(const void *d, long len)
{
  sensors_data data;

  memcpy(&data, d, len);
  auto x = std::chrono::system_clock::now() - m_time_start;
  double x_sec =
      std::chrono::duration_cast<std::chrono::milliseconds>(x).count() / 1000.0;

  m_chartAccel_1->m_series_x->append(x_sec, data.p1.ax);
  m_chartAccel_1->m_series_y->append(x_sec, data.p1.ay);
  m_chartAccel_1->m_series_z->append(x_sec, data.p1.ay);

  m_chartGyro_1->m_series_x->append(x_sec, data.p1.gx);
  m_chartGyro_1->m_series_y->append(x_sec, data.p1.gy);
  m_chartGyro_1->m_series_z->append(x_sec, data.p1.gz);

  m_chartAccel_2->m_series_x->append(x_sec, data.p2.ax);
  m_chartAccel_2->m_series_y->append(x_sec, data.p2.ay);
  m_chartAccel_2->m_series_z->append(x_sec, data.p2.ay);

  m_chartGyro_2->m_series_x->append(x_sec, data.p2.gx);
  m_chartGyro_2->m_series_y->append(x_sec, data.p2.gy);
  m_chartGyro_2->m_series_z->append(x_sec, data.p2.gz);

  m_chartAccel_3->m_series_x->append(x_sec, data.p3.ax);
  m_chartAccel_3->m_series_y->append(x_sec, data.p3.ay);
  m_chartAccel_3->m_series_z->append(x_sec, data.p3.ay);

  m_chartGyro_3->m_series_x->append(x_sec, data.p3.gx);
  m_chartGyro_3->m_series_y->append(x_sec, data.p3.gy);
  m_chartGyro_3->m_series_z->append(x_sec, data.p3.gz);

  if (x_sec >= m_chartAccel_1->getXAxisMax()) {
    m_chartAccel_1->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGyro_1->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartAccel_2->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGyro_2->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartAccel_3->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGyro_3->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
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
