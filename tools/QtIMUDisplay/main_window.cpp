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
#include <QtWidgets/QMainWindow>
#include <iostream>
#include "chart.h"
#include "common_types.h"
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
  QPushButton *Next = new QPushButton("NEXT", this);

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

  GaiInsLay->addWidget(Next, 0, Qt::AlignCenter);
  GaiInsLayWid->setLayout(GaiInsLay);
  GaiInsLayWid->show();

  QFont font_next("Arial", 40);
  font_next.setBold(true);
  Next->setFont(font_next);

  Next->setStyleSheet("background-color: white");
  Next->setMinimumSize(150, 100);

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

void MainWindow::on_message(const void *d, long len)
{
  sensors_data data;

  memcpy(&data, d, len);

  if (!m_time_started) {
    m_time_start = data.timepoint;
    m_time_started = true;
  }

  double x_sec = data.timepoint - m_time_start;

  m_chartAccel_1->m_series_x->append(x_sec, data.a.ax);
  m_chartAccel_1->m_series_y->append(x_sec, data.a.ay);
  m_chartAccel_1->m_series_z->append(x_sec, data.a.az);

  m_chartGyro_1->m_series_x->append(x_sec, data.a.gx);
  m_chartGyro_1->m_series_y->append(x_sec, data.a.gy);
  m_chartGyro_1->m_series_z->append(x_sec, data.a.gz);

  m_chartAccel_2->m_series_x->append(x_sec, data.b.ax);
  m_chartAccel_2->m_series_y->append(x_sec, data.b.ay);
  m_chartAccel_2->m_series_z->append(x_sec, data.b.az);

  m_chartGyro_2->m_series_x->append(x_sec, data.b.gx);
  m_chartGyro_2->m_series_y->append(x_sec, data.b.gy);
  m_chartGyro_2->m_series_z->append(x_sec, data.b.gz);

  m_chartAccel_3->m_series_x->append(x_sec, data.c.ax);
  m_chartAccel_3->m_series_y->append(x_sec, data.c.ay);
  m_chartAccel_3->m_series_z->append(x_sec, data.c.az);

  m_chartGyro_3->m_series_x->append(x_sec, data.c.gx);
  m_chartGyro_3->m_series_y->append(x_sec, data.c.gy);
  m_chartGyro_3->m_series_z->append(x_sec, data.c.gz);

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
  QDir().mkdir("savedata");

  QString timestamp =
      QDateTime::currentDateTime().toString("yy.MM.dd-hh:mm:ss");
  QString filename = "savedata/" + timestamp + ".json";
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }
  file.write(json.toJson());

  qDebug() << "Datapoints saved to file " << filename;
}
