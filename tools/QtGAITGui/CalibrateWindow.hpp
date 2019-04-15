#ifndef CalibrateWindow_hpp
#define CalibrateWindow_hpp

#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QtWidgets/QMainWindow>
#include "WindowBase.hpp"
#include <stdio.h>
#include <CircleWidget.hpp>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "WindowBase.hpp"
#include <QTimer>

class CalibrateWindow : public WindowBase {
 public:
  CalibrateWindow(int a, QMainWindow *parent);
  ~CalibrateWindow();
  void calibrate();

 private:
  int nextWindowId;
  int calibration_points;
  double pointsSumL = 0, pointsSumR = 0;
  QPushButton *CalibrateButton;
  QLabel *CalibrateText;

  void onCalibrateDone();

 private slots:
  void onCalibrateButtonPushed();
    void calibrateL(fsr_packet data);
    void calibrateR(fsr_packet data);

};

#endif /* CalibrateWindow_hpp */
