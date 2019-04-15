#ifndef CalibrateWindow_hpp
#define CalibrateWindow_hpp

#include <stdio.h>
#include <CircleWidget.hpp>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "WindowBase.hpp"
#include "common_types.h"
#include "progressbar.hpp"

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
  QProgressBar *CalibrationProgressBar;

  void onCalibrateDone();

 private slots:
  void onCalibrateButtonPushed();
  void calibrateL(fsr_data data);
  void calibrateR(fsr_data data);
};

#endif /* CalibrateWindow_hpp */
