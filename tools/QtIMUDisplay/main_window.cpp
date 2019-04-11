#include "main_window.h"
#include <QCheckBox>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QSplineSeries>
#include <QtCharts/QChartView>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>
#include <iostream>
#include "chart.h"
#include "progressbar.hpp"

MainWindow::MainWindow()
    : GaitInstructions(new QLabel()),
      m_chartAccel_1(new Chart()),
      m_chartGyro_1(new Chart()),
      m_chartAccel_2(new Chart()),
      m_chartGyro_2(new Chart()),
      m_chartAccel_3(new Chart()),
      m_chartGyro_3(new Chart()),
      m_chartGRF_r(new Chart()),
      m_chartGRF_l(new Chart())
{
  GaitInstructions->setText(R"(
  <html>
        <center>Welcome to Gait Mode!</center>
        <br>
        <blockquote>In this mode you will receive notification when any walking abnormality is detected.<\blockquote>
        <br>
        <blockquote>Please, indicate your desired feedback modalities.<\blockquote>
        <br>
        <blockquote>You can disconnect the device from your computer.<\blockquote>
  </html>)");

  GaitInstructions->setWordWrap(true);

  QFont font_message = GaitInstructions->font();
  font_message.setPixelSize(28);
  GaitInstructions->setFont(font_message);

  QCheckBox *Vocal_feedback = new QCheckBox("Vocal Feedback", this);
  QCheckBox *Vibro_feedback = new QCheckBox("Vibration", this);
  QPushButton *OK = new QPushButton("OK", this);

  QFont CheckBoxes("Arial", 22);
  Vocal_feedback->setFont(CheckBoxes);
  Vibro_feedback->setFont(CheckBoxes);

  QWidget *GaiInsLayWid = new QWidget();

  auto *GaiInsLay = new QVBoxLayout();
  GaiInsLay->addWidget(GaitInstructions, 0, Qt::AlignCenter);

  GaiInsLay->addLayout([&] {
    QHBoxLayout *l = new QHBoxLayout();
    l->addWidget(Vocal_feedback, 0, Qt::AlignCenter);
    l->addWidget(Vibro_feedback, 0, Qt::AlignCenter);
    return l;
  }());

  GaiInsLay->addWidget(OK, 0, Qt::AlignCenter);
  GaiInsLayWid->setLayout(GaiInsLay);
  GaiInsLayWid->show();

  QFont font_OK("Arial", 40);
  font_OK.setBold(true);
  OK->setFont(font_OK);

  OK->setStyleSheet("background-color: white");
  OK->setMinimumSize(100, 75);

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

  m_chartGRF_r->setTitle("Force data chart - Right foot");
  m_chartGRF_r->legend()->hide();
  m_chartGRF_l->setTitle("Force data chart - Left foot");
  m_chartGRF_l->legend()->hide();

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

  QCheckBox *Box4 = new QCheckBox("Sum");
  Box4->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box4, &QCheckBox::stateChanged, m_chartGRF_r->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box4, &QCheckBox::stateChanged, m_chartGRF_l->m_series_z,
                   &QAbstractSeries::setVisible);

  // Connect interface
  m_connectURI = new QLineEdit(this);
  m_connectButton = new QPushButton("connect", this);
  QHBoxLayout *connectInterfaceLayout = new QHBoxLayout(this);
  connectInterfaceLayout->addWidget(m_connectURI);
  connectInterfaceLayout->addWidget(m_connectButton);

  connect(m_connectButton, &QPushButton::clicked, this,
          &MainWindow::onConnectClicked);

  QPushButton *saveDataButton = new QPushButton("save data", this);

  // Charts
  QChartView *chartView_1 = new QChartView(m_chartAccel_1, this);
  QChartView *chartView_2 = new QChartView(m_chartGyro_1, this);
  QChartView *chartView_3 = new QChartView(m_chartAccel_2, this);
  QChartView *chartView_4 = new QChartView(m_chartGyro_2, this);
  QChartView *chartView_5 = new QChartView(m_chartAccel_3, this);
  QChartView *chartView_6 = new QChartView(m_chartGyro_3, this);
  QChartView *chartView_7 = new QChartView(m_chartGRF_r, this);
  QChartView *chartView_8 = new QChartView(m_chartGRF_l, this);

  chartView_1->setRenderHint(QPainter::Antialiasing);
  chartView_2->setRenderHint(QPainter::Antialiasing);
  chartView_3->setRenderHint(QPainter::Antialiasing);
  chartView_4->setRenderHint(QPainter::Antialiasing);
  chartView_5->setRenderHint(QPainter::Antialiasing);
  chartView_6->setRenderHint(QPainter::Antialiasing);
  chartView_7->setRenderHint(QPainter::Antialiasing);
  chartView_8->setRenderHint(QPainter::Antialiasing);

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
  layout_boxes->addWidget(saveDataButton);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(connectInterfaceLayout);
  layout->addLayout(layout_graphs1);
  layout->addLayout(layout_graphs2);
  layout->addLayout(layout_graphs3);
  layout->addLayout(layout_boxes);

  QTabWidget *TabAccGyro = new QTabWidget();

  QWidget *charts_IMU = new QWidget(this);
  TabAccGyro->addTab(charts_IMU, "IMUs");
  charts_IMU->setLayout(layout);

  QVBoxLayout *layout_graphs_FSR = new QVBoxLayout(this);
  layout_graphs_FSR->addWidget(chartView_7);
  layout_graphs_FSR->addWidget(chartView_8);
  layout_graphs_FSR->addWidget(Box4);

  QWidget *charts_FSR = new QWidget(this);
  TabAccGyro->addTab(charts_FSR, "FSRs");
  charts_FSR->setLayout(layout_graphs_FSR);
  setCentralWidget(TabAccGyro);

  connect(saveDataButton, &QPushButton::clicked, this,
          &MainWindow::onSaveClicked);

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
  delete m_chartGRF_r;
  delete m_chartGRF_l;
}

struct imu_packet {
  float ax, ay, az;
  float gx, gy, gz;
};

struct fsr_packet {
  float heel, toe;
};

struct sensors_data {
  imu_packet p1, p2, p3;
  fsr_packet right, left;
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
  m_chartAccel_1->m_series_z->append(x_sec, data.p1.az);

  m_chartGyro_1->m_series_x->append(x_sec, data.p1.gx);
  m_chartGyro_1->m_series_y->append(x_sec, data.p1.gy);
  m_chartGyro_1->m_series_z->append(x_sec, data.p1.gz);

  m_chartAccel_2->m_series_x->append(x_sec, data.p2.ax);
  m_chartAccel_2->m_series_y->append(x_sec, data.p2.ay);
  m_chartAccel_2->m_series_z->append(x_sec, data.p2.az);

  m_chartGyro_2->m_series_x->append(x_sec, data.p2.gx);
  m_chartGyro_2->m_series_y->append(x_sec, data.p2.gy);
  m_chartGyro_2->m_series_z->append(x_sec, data.p2.gz);

  m_chartAccel_3->m_series_x->append(x_sec, data.p3.ax);
  m_chartAccel_3->m_series_y->append(x_sec, data.p3.ay);
  m_chartAccel_3->m_series_z->append(x_sec, data.p3.az);

  m_chartGyro_3->m_series_x->append(x_sec, data.p3.gx);
  m_chartGyro_3->m_series_y->append(x_sec, data.p3.gy);
  m_chartGyro_3->m_series_z->append(x_sec, data.p3.gz);

  m_chartGRF_r->m_series_x->append(x_sec, data.right.toe);
  m_chartGRF_r->m_series_y->append(x_sec, data.right.heel);
  m_chartGRF_r->m_series_z->append(x_sec, data.right.toe + data.right.heel);

  m_chartGRF_l->m_series_x->append(x_sec, data.left.toe);
  m_chartGRF_l->m_series_y->append(x_sec, data.left.heel);
  m_chartGRF_l->m_series_z->append(x_sec, data.left.toe + data.left.heel);

  if (x_sec >= m_chartAccel_1->getXAxisMax()) {
    m_chartAccel_1->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGyro_1->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartAccel_2->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGyro_2->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartAccel_3->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGyro_3->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGRF_r->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
    m_chartGRF_l->axes(Qt::Horizontal).back()->setRange(x_sec - 10, x_sec);
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

void MainWindow::onSaveClicked()
{
  QJsonObject root;

  m_chartGRF_l->saveToJson(root, "FSR_L");
  m_chartGRF_r->saveToJson(root, "FSR_R");

  m_chartAccel_1->saveToJson(root, "acceleration_A");
  m_chartAccel_2->saveToJson(root, "acceleration_B");
  m_chartAccel_3->saveToJson(root, "acceleration_C");

  m_chartGyro_1->saveToJson(root, "gyroscope_A");
  m_chartGyro_2->saveToJson(root, "gyroscope_B");
  m_chartGyro_3->saveToJson(root, "gyroscope_C");

  QJsonDocument json(root);

  auto savepath = QCoreApplication::applicationDirPath() + "/savedata/";
  QDir().mkdir(savepath);

  QString savename = QDateTime::currentDateTime().toString("yy.MM.dd-hh:mm:ss");

  QString filename = savepath + savename + ".json";
  filename =
      QFileDialog::getSaveFileName(this, "Save Datapoints as Json", filename);

  if (filename.isEmpty())
    return;

  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }
  file.write(json.toJson());

  qDebug() << "Datapoints saved to file " << filename;
}
