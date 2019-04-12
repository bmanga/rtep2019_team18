#ifndef WelcomeWindow_hpp
#define WelcomeWindow_hpp
#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
<<<<<<< HEAD
#include "WindowBase.hpp"

class WelcomeWindow : public WindowBase {
  Q_OBJECT
 public:
  WelcomeWindow();
  ~WelcomeWindow();
 private slots:
  void onNextButtonPushed();
=======

class WelcomeWindow : public QWidget {
 public:
  WelcomeWindow();
  ~WelcomeWindow();
>>>>>>> Edited GUI, now works with realtime data from sensors.

 private:
  QLineEdit *ConnectLabel;
  QPushButton *ConnectButton;
  QCheckBox *VocalInstructions;
  QPushButton *NextButton;
  QLabel *WelcomeText;
};

#endif /* WelcomeWindow_hpp */
