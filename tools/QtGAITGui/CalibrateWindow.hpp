#ifndef CalibrateWindow_hpp
#define CalibrateWindow_hpp

#include <stdio.h>
<<<<<<< HEAD
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
=======
>>>>>>> Changed sensor structs to use common_types. Fixed calibrate window done signal.
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
<<<<<<< HEAD
#include <QTimer>
<<<<<<< HEAD
=======
>>>>>>> Changed sensor structs to use common_types. Fixed calibrate window done signal.

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
<<<<<<< HEAD
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
=======
  void calibrateL(fsr_data data);
  void calibrateR(fsr_data data);
>>>>>>> Changed sensor structs to use common_types. Fixed calibrate window done signal.
};

#endif /* CalibrateWindow_hpp */
