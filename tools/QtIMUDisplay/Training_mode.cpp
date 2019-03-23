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
      left_label_CP(new QLabel()),
      right_label_CP(new QLabel()),
      my_circle_r(new CircleWidget()),
      my_circle_l(new CircleWidget())

{
  // Weight shifting
  force_l->bufferLengthChanged(100);
  force_l->playPositionChanged(70);
  left_label_WS->setText("Left");
  left_label_WS->setAlignment(Qt::AlignCenter);
  QFont font_label("Arial", 48);
  left_label_WS->setFont(font_label);

  right_label_WS->setText("Right");
  right_label_WS->setFont(font_label);
  right_label_WS->setAlignment(Qt::AlignCenter);
  force_r->bufferLengthChanged(100);
  force_r->playPositionChanged(10);

  // Weight shifting
  my_circle_r->setDiameter(100);
  my_circle_l->setDiameter(100);
  left_label_CP->setText("Left");
  left_label_CP->setAlignment(Qt::AlignCenter);
  left_label_CP->setFont(font_label);

  right_label_CP->setText("Right");
  right_label_CP->setAlignment(Qt::AlignCenter);
  right_label_CP->setFont(font_label);

  // TRAINING MODE

  QTabWidget *Training = new QTabWidget();

  QWidget *Weight_shift = new QWidget();
  QGridLayout *Weight_shift_grid = new QGridLayout();
  Weight_shift_grid->addWidget(left_label_WS, 0, 0);
  Weight_shift_grid->addWidget(force_l, 1, 0, Qt::AlignCenter);
  Weight_shift_grid->addWidget(right_label_WS, 0, 1);
  Weight_shift_grid->addWidget(force_r, 1, 1, Qt::AlignCenter);
  Weight_shift->setLayout(Weight_shift_grid);
  Training->addTab(Weight_shift, "Weight Shift");

  QWidget *Calf_push = new QWidget();
  QGridLayout *Calf_push_grid = new QGridLayout();
  Calf_push_grid->addWidget(left_label_CP, 0, 0);
  Calf_push_grid->addWidget(my_circle_r, 1, 0, Qt::AlignCenter);
  Calf_push_grid->addWidget(right_label_CP, 0, 1);
  Calf_push_grid->addWidget(my_circle_l, 1, 1, Qt::AlignCenter);
  Calf_push->setLayout(Calf_push_grid);
  Training->addTab(Calf_push, "Calf Push");
  Training->show();
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

  memcpy(&data, d, len);
  auto x = std::chrono::system_clock::now() - m_time_start;
  double x_sec =
      std::chrono::duration_cast<std::chrono::milliseconds>(x).count() / 1000.0;

  force_r_toe->playPositionChanged(data.right.toe);
  force_r_heel->playPositionChanged(data.right.heel);
  force_r->playPositionChanged(data.right.toe + data.right.heel);

  force_l_toe->playPositionChanged(data.left.toe);
  force_l_heel->playPositionChanged(data.left.heel);
  force_l->playPositionChanged(data.left.toe + data.left.heel);
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
  // ProgressBar::disconnect(m_connectButton, &QPushButton::clicked, this,
  //    &TrainingMode::onConnectClicked); gives error
  //  ProgressBar::connect(m_connectButton, &QPushButton::clicked, this,
  //   &TrainingMode::onDisconnectClicked);
}

void TrainingMode::onDisconnectClicked()
{
  m_connectButton->setText("connect");
  // ProgressBar::disconnect(m_connectButton, &QPushButton::clicked, this,
  //    &TrainingMode::onDisconnectClicked);
  // ProgressBar::connect(m_connectButton, &QPushButton::clicked, this,
  //  &TrainingMode::onConnectClicked);
}

TrainingMode::~TrainingMode()
{
  delete force_r_toe;
  delete force_r_heel;
  delete force_r;
  delete force_l_toe;
  delete force_l_heel;
  delete force_l;
}
