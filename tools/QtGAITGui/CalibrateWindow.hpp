#ifndef CalibrateWindow_hpp
#define CalibrateWindow_hpp

#include <stdio.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Added calibration functionality.
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
#include "progressbar.hpp"
#include <QTimer>
<<<<<<< HEAD

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
    void calibrateL(fsr_packet data);
    void calibrateR(fsr_packet data);

=======
=======
#include "WindowBase.hpp"
>>>>>>> qt gui: all windows in training mode are now connected
=======
>>>>>>> Added calibration functionality.

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
<<<<<<< HEAD
>>>>>>> Edited GUI, now works with realtime data from sensors.
=======

  void onCalibrateDone();

 private slots:
  void onCalibrateButtonPushed();
<<<<<<< HEAD
>>>>>>> qt gui: all windows in training mode are now connected
=======
    void calibrateL(fsr_packet data);
    void calibrateR(fsr_packet data);

>>>>>>> Added calibration functionality.
};

#endif /* CalibrateWindow_hpp */
