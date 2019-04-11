#include "Training_mode.hpp"
#include <QCheckBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QSplineSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "CircleWidget.hpp"
#include "Level_weight_shifting.hpp"
#include "chart.h"
#include "main_window.h"
#include "progressbar.hpp"

TrainingMode::TrainingMode()
    : TrainInstructions(new QLabel()),
      force_r(new ProgressBar()),
      force_l(new ProgressBar()),
      left_label_WS(new QLabel()),
      right_label_WS(new QLabel()),
      my_circle_r(new CircleWidget()),
      my_circle_l(new CircleWidget()),
      left_label_CP(new QLabel()),
      right_label_CP(new QLabel()),
      communication_label_WS(new QLabel()),
      communication_label_CP(new QLabel()),
      level_label_WS(new QLabel()),
      level_label_CP(new QLabel())

{
  TrainInstructions->setText(R"(
  <html>
      <center>Welcome to Training Mode!</center>
      <br>
      <ul>
      There are two exercises you can choose from. Please follow you physiotherapist's advice.
      <br>
          <blockquote><b>Weight Shift</b> to shift your body weight from one leg to the other.</blockquote>
          <br>
          <blockquote><b>Calf Push</b> to shift your body weight from heel to toes. </blockquote>
          <br>
      </ul>
  </html>)");
  TrainInstructions->setWordWrap(true);

  QFont font_message = TrainInstructions->font();
  font_message.setPixelSize(28);
  TrainInstructions->setFont(font_message);

  QPushButton *WSButton = new QPushButton("Weight Shift", this);
  QPushButton *CPButton = new QPushButton("Calf Push", this);

  QFont CheckBoxes("Arial", 22);
  WSButton->setFont(CheckBoxes);
  CPButton->setFont(CheckBoxes);

  QWidget *TraInsLayWid = new QWidget();

  auto *TraInsLay = new QVBoxLayout();
  TraInsLay->addWidget(TrainInstructions, 0, Qt::AlignCenter);

  TraInsLay->addLayout([&] {
    QHBoxLayout *l = new QHBoxLayout();
    l->addWidget(WSButton);
    l->addSpacing(50);
    l->addWidget(CPButton);
    return l;
  }());
  TraInsLayWid->setLayout(TraInsLay);
  TraInsLayWid->show();

  QFont font_tra_buttons("Arial", 40);
  font_tra_buttons.setBold(true);
  WSButton->setFont(font_tra_buttons);
  WSButton->setStyleSheet("background-color: white");
  CPButton->setFont(font_tra_buttons);
  CPButton->setStyleSheet("background-color: white");
  left_label_WS->setText("Left");
  QFont font_comm_level("Arial", 28);
  QFont font_label_level("Arial", 48);
  QFont font_label_foot("Arial", 36);
  left_label_WS->setFont(font_label_foot);
  right_label_WS->setText("Right");
  right_label_WS->setFont(font_label_foot);
  communication_label_WS->setText(R"(
  <html>
        <center>Shift your body weight from one leg to the other to hit the green target in each bar.</center>
  </html>)");
  communication_label_WS->setWordWrap(true);
  communication_label_WS->setFont(font_comm_level);
  level_label_WS->setText("Level 1");
  level_label_WS->setAlignment(Qt::AlignCenter);
  level_label_WS->setFont(font_label_level);

  left_label_CP->setText("Left");
  left_label_CP->setFont(font_label_foot);
  right_label_CP->setText("Right");
  right_label_CP->setFont(font_label_foot);
  communication_label_CP->setText(R"(
                                  <html>
                                  <center>Shift your body weight from heel to toes to hit the green target in each bar.</center>
                                  </html>)");
  communication_label_CP->setWordWrap(true);
  communication_label_CP->setFont(font_comm_level);
  level_label_CP->setText("Level 1");
  level_label_CP->setAlignment(Qt::AlignCenter);
  level_label_CP->setFont(font_label_level);

  m_connectURI = new QLineEdit(this);
  m_connectButton = new QPushButton("connect", this);
  QHBoxLayout *connectInterfaceLayout = new QHBoxLayout(this);
  connectInterfaceLayout->addWidget(m_connectURI);
  connectInterfaceLayout->addWidget(m_connectButton);

  QTabWidget *Training = new QTabWidget();
  QWidget *Weight_shift = new QWidget();
  QVBoxLayout *Weight_shift_complete = new QVBoxLayout(Weight_shift);
  QGridLayout *Weight_shift_grid = new QGridLayout(Weight_shift);
  Weight_shift_grid->addWidget(left_label_WS, 2, 0, Qt::AlignCenter);
  Weight_shift_grid->addWidget(force_l, 1, 0, Qt::AlignCenter);
  Weight_shift_grid->addWidget(right_label_WS, 2, 1, Qt::AlignCenter);
  Weight_shift_grid->addWidget(force_r, 1, 1, Qt::AlignCenter);

  LevelWS *lev = new LevelWS(force_l, force_r);
  lev->setLvlRequirements({0.2, 0.5}, {0.5, 0.8}, std::chrono::seconds(5));

  Weight_shift_complete->addLayout(connectInterfaceLayout);
  Weight_shift_complete->addWidget(communication_label_WS);
  Weight_shift_complete->addWidget(level_label_WS);
  Weight_shift_complete->addLayout(Weight_shift_grid);
  Weight_shift->setLayout(Weight_shift_complete);
  Training->addTab(Weight_shift, "Weight Shift");

  QWidget *Calf_push = new QWidget();
  QVBoxLayout *Calf_push_complete = new QVBoxLayout(Calf_push);
  QGridLayout *Calf_push_grid = new QGridLayout();
  Calf_push_grid->addWidget(left_label_CP, 2, 0, Qt::AlignCenter);
  Calf_push_grid->addWidget(my_circle_r, 1, 0, Qt::AlignCenter);
  Calf_push_grid->addWidget(right_label_CP, 2, 1, Qt::AlignCenter);
  Calf_push_grid->addWidget(my_circle_l, 1, 1, Qt::AlignCenter);
  Calf_push_complete->addWidget(communication_label_CP);
  Calf_push_complete->addSpacing(20);
  Calf_push_complete->addWidget(level_label_CP);
  Calf_push_complete->addLayout(Calf_push_grid);
  Calf_push->setLayout(Calf_push_complete);
  Training->addTab(Calf_push, "Calf Push");
  Training->show();

  connect(m_connectButton, &QPushButton::clicked, this,
          &TrainingMode::onConnectClicked);

  connect(this, &TrainingMode::newForceRData, force_r,
          &ProgressBar::playPositionChanged);
  connect(this, &TrainingMode::newForceLData, force_l,
          &ProgressBar::playPositionChanged);
  connect(this, &TrainingMode::newForceRToeData, my_circle_r,
          &CircleWidget::setDiameter);
  connect(this, &TrainingMode::newForceLToeData, my_circle_l,
          &CircleWidget::setDiameter);

  m_client.set_message_handler(
      [this](const void *data, long len) { this->on_message(data, len); });
}
TrainingMode::~TrainingMode()
{
  delete force_r_toe;
  delete force_r_heel;
  delete force_r;
  delete force_l_toe;
  delete force_l_heel;
  delete force_l;
  delete left_label_WS;
  delete right_label_WS;
  delete left_label_CP;
  delete right_label_CP;
  delete my_circle_r;
  delete my_circle_l;
}

struct fsr_packet {
  float heel, toe;
};
struct sensors_data {
  fsr_packet right, left;
};

void TrainingMode::on_message(const void *d, long len)
{
  sensors_data data;

  memcpy(&data, d, sizeof(data));

  emit newForceRData(data.right.toe + data.right.heel);
  emit newForceRToeData(data.right.toe);
  emit newForceRHeelData(data.right.heel);
  emit newForceLData(data.left.toe + data.left.heel);
  emit newForceLToeData(data.left.toe);
  emit newForceLHeelData(data.left.heel);
}

void TrainingMode::onConnectClicked()
{
  m_time_start = std::chrono::system_clock::now();
  QString uri = m_connectURI->text();
  if (uri == "")
    return;
  m_client.connect_to(uri.toStdString());
  m_client.run_on_thread();
  m_connectButton->setText("disconnect");
  disconnect(m_connectButton, &QPushButton::clicked, this,
             &TrainingMode::onConnectClicked);
  connect(m_connectButton, &QPushButton::clicked, this,
          &TrainingMode::onDisconnectClicked);
}

void TrainingMode::onDisconnectClicked()
{
  m_connectButton->setText("connect");
  disconnect(m_connectButton, &QPushButton::clicked, this,
             &TrainingMode::onDisconnectClicked);
  connect(m_connectButton, &QPushButton::clicked, this,
          &TrainingMode::onConnectClicked);
}
