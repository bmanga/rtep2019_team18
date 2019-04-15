#include "CalibrateWindow.hpp"
#include <stdio.h>
#include <CircleWidget.hpp>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QVBoxLayout>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "MainWindow.hpp"
#include "WindowBase.hpp"
#include "common_types.h"
#include "progressbar.hpp"
#include "telemetry/client.h"

CalibrateWindow::CalibrateWindow(int a, QMainWindow *parent)
    : WindowBase(parent),
      nextWindowId(a),
      CalibrateButton(new QPushButton()),
      CalibrateText(new QLabel()),
      CalibrationProgressBar(new QProgressBar())
{
  CalibrateText->setText(R"(
                       <html>
                         <blockquote> <blockquote> <b>STEP 3:</b> Before your training begins, please click on <b>Calibrate</b> and stand still for few seconds.  </blockquote> </blockquote>
                       </html>)");

  CalibrateText->setWordWrap(true);
  QFont font_message = CalibrateText->font();
  font_message.setPixelSize(28);
  CalibrateText->setFont(font_message);

  QFont font_next = CalibrateButton->font();
  font_next.setPixelSize(30);
  CalibrateButton->setFont(font_next);
  CalibrateButton->setText("Calibrate");

  QHBoxLayout *CalButtLay = new QHBoxLayout();
  CalButtLay->addSpacing(200);
  CalButtLay->addWidget(CalibrateButton);
  CalButtLay->addSpacing(200);

  CalibrationProgressBar->setMaximum(100);
  // CalibrationProgressBar->setOrientation

  QVBoxLayout *CalibrateLay = new QVBoxLayout();
  CalibrateLay->addWidget(CalibrateText);
  CalibrateLay->addSpacing(30);
  CalibrateLay->addLayout(CalButtLay);
  CalibrateLay->addSpacing(250);
  CalibrateLay->addWidget(CalibrationProgressBar);
  setLayout(CalibrateLay);

  QPalette pal = palette();
  QColor background(204, 225, 255);
  pal.setColor(QPalette::Background, background);
  setAutoFillBackground(true);
  setPalette(pal);
  connect(CalibrateButton, &QPushButton::clicked, this,
          &CalibrateWindow::onCalibrateButtonPushed);

  calibration_points = 0;
}
CalibrateWindow::~CalibrateWindow()
{
  delete CalibrateButton;
  delete CalibrateText;
}

void CalibrateWindow::onCalibrateButtonPushed()
{
  connect(static_cast<MainWindow *>(this->parent()), &MainWindow::newFSRDataL,
          this, &CalibrateWindow::calibrateL);
  connect(static_cast<MainWindow *>(this->parent()), &MainWindow::newFSRDataR,
          this, &CalibrateWindow::calibrateR);

  // emit windowDone(WindowKind::Cal, this->nextWindowId);
}

void CalibrateWindow::calibrateL(fsr_data data)
{
  pointsSumL += data.toe + data.heel;
}

void CalibrateWindow::calibrateR(fsr_data data)
{
  if (calibration_points < 100) {
    calibration_points += 1;
    pointsSumR += data.toe + data.heel;
    CalibrationProgressBar->setValue(calibration_points);
  }
  else {
    onCalibrateDone();  // disconnect(static_cast<MainWindow *>(parent),
                        // &MainWindow::newFSRDataL,
    // this, this::calibrate);
  }
}

void CalibrateWindow::onCalibrateDone()
{
  double max = (pointsSumL + pointsSumR) / 100;
  printf("Points SumL: %f\n", pointsSumL);
  printf("Points SumR: %f\n", pointsSumR);
  printf("Calibrate Done Max: %f\n", max);
  // call parent and set max
  static_cast<MainWindow *>(parent())->setCalibrationMax(max);
  emit windowDone(WindowKind::Cal, this->nextWindowId);
}
