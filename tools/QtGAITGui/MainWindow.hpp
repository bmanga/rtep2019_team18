#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <stdio.h>
#include <CircleWidget.hpp>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QMetaType>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "WindowBase.hpp"
#include "common_types.h"
#include "telemetry/client.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  ~MainWindow();

  void setCalibrationMax(double max);
  double calibrationMax;

 signals:
  void newFSRDataL(fsr_data);
  void newFSRDataR(fsr_data);

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
