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
class CircleWidget;

class TrainingMode : public QMainWindow {
  Q_OBJECT
 public:
  TrainingMode();
  ~TrainingMode();

 signals:
  void newForceRData(float value);
  void newForceRToeData(float value);
  void newForceRHeelData(float value);
  void newForceLData(float value);
  void newForceLToeData(float value);
  void newForceLHeelData(float value);

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
  CircleWidget *my_circle_r;
  CircleWidget *my_circle_l;
  QLabel *left_label_WS;
  QLabel *right_label_WS;
  QLabel *left_label_CP;
  QLabel *right_label_CP;
  QLabel *communication_label_WS;
  QLabel *communication_label_CP;
  std::chrono::system_clock::time_point m_time_start;
  QLineEdit *m_connectURI;
  QPushButton *m_connectButton;
};

#endif /* Training_mode_hpp */
