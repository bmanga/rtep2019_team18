#include "MainWindow.hpp"
<<<<<<< HEAD
<<<<<<< HEAD
#include "CalibrateWindow.hpp"
#include "FinalWindow.hpp"
#include "Training_mode.hpp"
#include "WelcomeWindow.hpp"
#include "intro_window.hpp"
=======
#include "CalibrateWindow.hpp"
#include "FinalWindow.hpp"
#include "Training_mode.hpp"
>>>>>>> qt gui: all windows in training mode are now connected

MainWindow::MainWindow()
{
  auto *welcomeScreen = new WelcomeWindow();
  setCentralWidget(welcomeScreen);
  connect(welcomeScreen, &WindowBase::windowDone, this,
          &MainWindow::onWindowDone);
<<<<<<< HEAD

  m_client.set_message_handler(
      [this](const void *data, long len) { this->on_message(data, len); });
=======
>>>>>>> qt gui: all windows in training mode are now connected
}

void MainWindow::onWindowDone(WindowKind wk, int extra)
{
  delete this->centralWidget();
  WindowBase *nextWindow = nullptr;
  switch (wk) {
    case WindowKind::Welcome:
      nextWindow = new IntroWindow();
      break;
    case WindowKind::Intro:
<<<<<<< HEAD
      nextWindow = new CalibrateWindow(extra, this);
=======
      nextWindow = new CalibrateWindow(extra);
>>>>>>> qt gui: all windows in training mode are now connected
      break;
    case WindowKind::Cal:
      if (extra == 0) {
        nextWindow = new TrainingMode<ProgressBar>(R"(
                                                   <html>
                                                   <center><b>Welcome to the Weight Shifting exercise!</b> <\center>
                                                   <br>
                                                   <br>
                                                   Shift your weight from one foot to the other to reach the target levels shown on each bar
                                                   <br>
                                                   
<<<<<<< HEAD
                                                   </html>)",
                                                   this);
=======
                                                   </html>)");
>>>>>>> qt gui: all windows in training mode are now connected
        ;
      }
      else {
        nextWindow = new TrainingMode<CircleWidget>(R"(
                                                    <html>
                                                    <center><b>Welcome to the Calf Pushes exercise!</b> <\center>
                                                    <br>
                                                    <br>
                                                    Shift your weight from heel to toes to  reach the target levels shown on each bar
                                                    <br>
<<<<<<< HEAD
                                                    </html>)",
                                                    this);
=======
                                                    </html>)");
>>>>>>> qt gui: all windows in training mode are now connected
        ;
      }

      break;
  }
  connect(nextWindow, &WindowBase::windowDone, this, &MainWindow::onWindowDone);
  this->setCentralWidget(nextWindow);
}
<<<<<<< HEAD

MainWindow::~MainWindow() {}

void MainWindow::on_message(const void *d, long len)
{
  sensors_data data = {};
  memcpy(&data, d, sizeof(data));

  emit newFSRDataL(data.left);
  emit newFSRDataR(data.right);
}

void MainWindow::setCalibrationMax(int maxValue)
{
    calibrationMax = maxValue;
}
=======
MainWindow::MainWindow() {}
=======
>>>>>>> qt gui: all windows in training mode are now connected

MainWindow::~MainWindow() {}
>>>>>>> Edited GUI, now works with realtime data from sensors.
