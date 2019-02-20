#ifndef main_window_hpp
#define main_window_hpp

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

 private:
  void on_message(const void *d, long len);

 private:
  tel::client m_client;
  Chart *m_chartAccel;
  Chart *m_chartGyro;
  std::chrono::system_clock::time_point m_time_start;
  QLineEdit *m_connectURI;
  QPushButton *m_connectButton;
};

#endif /* main_window_hpp */
