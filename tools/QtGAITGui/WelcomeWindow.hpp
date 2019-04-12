#ifndef WelcomeWindow_hpp
#define WelcomeWindow_hpp
#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class WelcomeWindow : public QWidget {
 public:
  WelcomeWindow();
  ~WelcomeWindow();

 private:
  QLineEdit *ConnectLabel;
  QPushButton *ConnectButton;
  QCheckBox *VocalInstructions;
  QPushButton *NextButton;
  QLabel *WelcomeText;
};

#endif /* WelcomeWindow_hpp */
