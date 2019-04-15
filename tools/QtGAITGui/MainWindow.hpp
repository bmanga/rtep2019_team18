#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <stdio.h>
<<<<<<< HEAD
<<<<<<< HEAD
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

=======
#include <CircleWidget.hpp>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
=======
#include <QMetaType>
>>>>>>> qt gui: training mode receiving data from sensors
#include <QString>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "WindowBase.hpp"

#include "telemetry/client.h"

<<<<<<< HEAD
>>>>>>> Edited GUI, now works with realtime data from sensors.
=======
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

>>>>>>> qt gui: training mode receiving data from sensors
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  ~MainWindow();
<<<<<<< HEAD
<<<<<<< HEAD
  void setCalibrationMax(int max);

  int calibrationMax;


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
=======

 signals:
  void newFSRDataL(fsr_packet);
  void newFSRDataR(fsr_packet);

 public slots:
  void onWindowDone(WindowKind win, int extra = 0);
  void connectToAddress(QString address)
  {
    address = "ws://" + address + ":9004";
<<<<<<< HEAD
    qDebug() << "address is: " << address;
>>>>>>> qt gui: all windows in training mode are now connected
=======
    m_client.connect_to(address.toStdString());
    m_client.run_on_thread();
>>>>>>> qt gui: training mode receiving data from sensors
  }

 private:
  tel::client m_client;
<<<<<<< HEAD
<<<<<<< HEAD
  void on_message(const void *d, long len);
=======
>>>>>>> Edited GUI, now works with realtime data from sensors.
=======
>>>>>>> qt gui: all windows in training mode are now connected
=======
  void on_message(const void *d, long len);
>>>>>>> qt gui: training mode receiving data from sensors
};

#endif /* MainWindow_hpp */
