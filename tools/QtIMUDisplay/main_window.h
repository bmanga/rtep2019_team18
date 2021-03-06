#ifndef main_window_hpp
#define main_window_hpp

#include <QLabel>
#include <QPainter>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "telemetry/client.h"

class Chart;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow {
 public:
  MainWindow();
  ~MainWindow();

 public slots:
  void onConnectClicked();
  void onDisconnectClicked();
  void onSaveClicked();

 private:
  void on_message(const void *d, long len);
  QLabel *GaitInstructions;

 private:
  tel::client m_client;
  Chart *m_chartAccel_1;
  Chart *m_chartGyro_1;
  Chart *m_chartAccel_2;
  Chart *m_chartGyro_2;
  Chart *m_chartAccel_3;
  Chart *m_chartGyro_3;
  Chart *m_chartGRF_r;
  Chart *m_chartGRF_l;

  float m_time_start;
  bool m_time_started = false;
  QLineEdit *m_connectURI;
  QPushButton *m_connectButton;
};

#endif /* main_window_hpp */
