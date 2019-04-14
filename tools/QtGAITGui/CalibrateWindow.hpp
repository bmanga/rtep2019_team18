#ifndef CalibrateWindow_hpp
#define CalibrateWindow_hpp

#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "WindowBase.hpp"

class CalibrateWindow : public WindowBase {
 public:
  CalibrateWindow(int a);
  ~CalibrateWindow();

 private:
  int nextWindowId;
  QPushButton *CalibrateButton;
  QLabel *CalibrateText;

 private slots:
  void onCalibrateButtonPushed();
};

#endif /* CalibrateWindow_hpp */
