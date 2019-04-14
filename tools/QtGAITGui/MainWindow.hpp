#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <stdio.h>
#include <CircleWidget.hpp>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "WelcomeWindow.hpp"
#include "WindowBase.hpp"
#include "intro_window.hpp"
#include "progressbar.hpp"
#include "telemetry/client.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  ~MainWindow();

 public slots:
  void onWindowDone(WindowKind win, int extra = 0);

  void connectToAddress(QString address)
  {
    address = "ws://" + address + ":9004";
    qDebug() << "address is: " << address;
  }

 private:
  tel::client m_client;
};

#endif /* MainWindow_hpp */
