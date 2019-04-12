#ifndef MainWindow_hpp
#define MainWindow_hpp

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

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  ~MainWindow();
};

#endif /* MainWindow_hpp */
