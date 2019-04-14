#ifndef WelcomeWindow_hpp
#define WelcomeWindow_hpp
#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
<<<<<<< HEAD
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
=======
#include "WindowBase.hpp"
>>>>>>> qt gui: all windows in training mode are now connected

class WelcomeWindow : public WindowBase {
  Q_OBJECT
 public:
  WelcomeWindow();
  ~WelcomeWindow();
<<<<<<< HEAD
>>>>>>> Edited GUI, now works with realtime data from sensors.
=======
 private slots:
  void onNextButtonPushed();
>>>>>>> qt gui: all windows in training mode are now connected

 private:
  QLineEdit *ConnectLabel;
  QPushButton *ConnectButton;
  QCheckBox *VocalInstructions;
  QPushButton *NextButton;
  QLabel *WelcomeText;
};

#endif /* WelcomeWindow_hpp */
