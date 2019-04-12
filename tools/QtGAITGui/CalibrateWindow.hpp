#ifndef CalibrateWindow_hpp
#define CalibrateWindow_hpp

#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class CalibrateWindow : public QWidget {
 public:
  CalibrateWindow();
  ~CalibrateWindow();

 private:
  QPushButton *CalibrateButton;
  QLabel *CalibrateText;
};

#endif /* CalibrateWindow_hpp */
