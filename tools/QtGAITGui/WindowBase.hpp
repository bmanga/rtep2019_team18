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
 signals:
  void windowDone(WindowKind, int);
};
