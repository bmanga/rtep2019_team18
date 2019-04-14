#include "MainWindow.hpp"
#include "CalibrateWindow.hpp"
#include "FinalWindow.hpp"
#include "Training_mode.hpp"

MainWindow::MainWindow()
{
  auto *welcomeScreen = new WelcomeWindow();
  setCentralWidget(welcomeScreen);
  connect(welcomeScreen, &WindowBase::windowDone, this,
          &MainWindow::onWindowDone);
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
      nextWindow = new CalibrateWindow(extra);
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
                                                   
                                                   </html>)");
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
                                                    </html>)");
        ;
      }

      break;
  }
  connect(nextWindow, &WindowBase::windowDone, this, &MainWindow::onWindowDone);
  this->setCentralWidget(nextWindow);
}

MainWindow::~MainWindow() {}
