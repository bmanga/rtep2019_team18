#ifndef WelcomeWindow_hpp
#define WelcomeWindow_hpp
#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "WindowBase.hpp"

class WelcomeWindow : public WindowBase {
  Q_OBJECT
 public:
  WelcomeWindow();
  ~WelcomeWindow();
 private slots:
  void onNextButtonPushed();

 private:
  QLineEdit *ConnectLabel;
  QPushButton *ConnectButton;
  QCheckBox *VocalInstructions;
  QPushButton *NextButton;
  QLabel *WelcomeText;
};

#endif /* WelcomeWindow_hpp */
