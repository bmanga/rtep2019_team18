#ifndef Training_mode_hpp
#define Training_mode_hpp

#include <stdio.h>
#include <CircleWidget.hpp>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "progressbar.hpp"
#include "telemetry/client.h"

class ProgressBar;

class TrainingMode {
 public:
  TrainingMode();
  ~TrainingMode();

 public slots:
  void onConnectClicked();
  void onDisconnectClicked();

 private:
  void on_message(const void *d, long len);

 private:
  tel::client m_client;
  ProgressBar *force_r_toe;
  ProgressBar *force_r_heel;
  ProgressBar *force_r;
  ProgressBar *force_l_toe;
  ProgressBar *force_l_heel;
  ProgressBar *force_l;
  QLabel *left_label_WS;
  QLabel *right_label_WS;
  QLabel *left_label_CP;
  QLabel *right_label_CP;
  std::chrono::system_clock::time_point m_time_start;
  QLineEdit *m_connectURI;
  QPushButton *m_connectButton;
  CircleWidget *my_circle_r;
  CircleWidget *my_circle_l;
};

#endif /* Training_mode_hpp */
