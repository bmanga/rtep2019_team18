#pragma once

#include <QWidget>

enum WindowKind {
  Welcome,
  Intro,
  Cal,
  Training,
  Final,
};

class WindowBase : public QWidget {
  Q_OBJECT
 public:
<<<<<<< HEAD
<<<<<<< HEAD
    WindowBase(QWidget *parent = nullptr) : QWidget(parent) {}
=======
>>>>>>> qt gui: all windows in training mode are now connected
=======
    WindowBase(QWidget *parent = nullptr) : QWidget(parent) {}
>>>>>>> Added calibration functionality.
 signals:
  void windowDone(WindowKind, int);
};
