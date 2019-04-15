#ifndef WelcomeWindow_hpp
#define WelcomeWindow_hpp
#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QtTextToSpeech/QTextToSpeech>
#include "WindowBase.hpp"

class WelcomeWindow : public WindowBase {
  Q_OBJECT
 public:
  WelcomeWindow();
  ~WelcomeWindow();
  void checkBoxClicked();
 private slots:
  void onNextButtonPushed();
  // void onVocalInstructionsChecked();

 private:
  QLineEdit *ConnectLabel;
  QLabel *ConnectText;
  QPushButton *ConnectButton;
  QCheckBox *VocalInstructions;
  QPushButton *NextButton;
  QLabel *WelcomeText;
  QTextToSpeech *m_speech;
};

#endif /* WelcomeWindow_hpp */
