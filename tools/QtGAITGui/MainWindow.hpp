#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <stdio.h>
#include <QMetaType>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "WindowBase.hpp"

#include "telemetry/client.h"

struct imu_packet {
  float ax, ay, az;
  float gx, gy, gz;
};

struct fsr_packet {
  float heel, toe;
};

Q_DECLARE_METATYPE(fsr_packet);

struct sensors_data {
  float timepoint;
  imu_packet p1, p2, p3;
  fsr_packet left, right;
};

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  ~MainWindow();

 signals:
  void newFSRDataL(fsr_packet);
  void newFSRDataR(fsr_packet);

 public slots:
  void onWindowDone(WindowKind win, int extra = 0);
  void connectToAddress(QString address)
  {
    address = "ws://" + address + ":9004";
    m_client.connect_to(address.toStdString());
    m_client.run_on_thread();
  }

 private:
  tel::client m_client;
  void on_message(const void *d, long len);
};

#endif /* MainWindow_hpp */
