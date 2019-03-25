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
#include "chart.h"
#include "main_window.h"
#include "progressbar.hpp"

TrainingMode::TrainingMode()
    : force_r_toe(new ProgressBar()),
      force_r_heel(new ProgressBar()),
      force_r(new ProgressBar()),
      force_l_toe(new ProgressBar()),
      force_l_heel(new ProgressBar()),
      force_l(new ProgressBar()),
      left_label_WS(new QLabel()),
      right_label_WS(new QLabel()),
      my_circle_r(new CircleWidget()),
      my_circle_l(new CircleWidget()),
      left_label_CP(new QLabel()),
      right_label_CP(new QLabel())

{
  // Weight shifting
  force_l->bufferLengthChanged(100);
  left_label_WS->setText("Left");
  QFont font_label("Arial", 48);
  left_label_WS->setFont(font_label);
  right_label_WS->setText("Right");
  right_label_WS->setFont(font_label);
  force_r->bufferLengthChanged(100);

  // Calf push
  my_circle_r->setDiameter(100);
  my_circle_l->setDiameter(100);
  left_label_CP->setText("Left");
  left_label_CP->setFont(font_label);
  right_label_CP->setText("Right");
  right_label_CP->setFont(font_label);

  // Connect button
  m_connectURI = new QLineEdit(this);
  m_connectButton = new QPushButton("connect", this);
  QHBoxLayout *connectInterfaceLayout = new QHBoxLayout(this);
  connectInterfaceLayout->addWidget(m_connectURI);
  connectInterfaceLayout->addWidget(m_connectButton);

  QTabWidget *Training = new QTabWidget();
  QWidget *Weight_shift = new QWidget();
  QVBoxLayout *Weight_shift_complete = new QVBoxLayout(Weight_shift);
  QGridLayout *Weight_shift_grid = new QGridLayout(Weight_shift);
  Weight_shift_grid->addWidget(left_label_WS, 0, 0, Qt::AlignCenter);
  Weight_shift_grid->addWidget(force_l, 1, 0, Qt::AlignCenter);
  Weight_shift_grid->addWidget(right_label_WS, 0, 1, Qt::AlignCenter);
  Weight_shift_grid->addWidget(force_r, 1, 1, Qt::AlignCenter);

  Weight_shift_complete->addLayout(connectInterfaceLayout);
  Weight_shift_complete->addLayout(Weight_shift_grid);
  Weight_shift->setLayout(Weight_shift_complete);
  Training->addTab(Weight_shift, "Weight Shift");

  QWidget *Calf_push = new QWidget();
  QGridLayout *Calf_push_grid = new QGridLayout();
  Calf_push_grid->addWidget(left_label_CP, 0, 0, Qt::AlignCenter);
  Calf_push_grid->addWidget(my_circle_r, 1, 0, Qt::AlignCenter);
  Calf_push_grid->addWidget(right_label_CP, 0, 1, Qt::AlignCenter);
  Calf_push_grid->addWidget(my_circle_l, 1, 1, Qt::AlignCenter);
  Calf_push->setLayout(Calf_push_grid);
  Training->addTab(Calf_push, "Calf Push");
  Training->show();

  // Signal connection
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
