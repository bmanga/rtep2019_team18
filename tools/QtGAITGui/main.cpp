#include <QSplashScreen>
#include <QtWidgets/QApplication>
#include "CalibrateWindow.hpp"
#include "CircleWidget.hpp"
#include "FinalWindow.hpp"
#include "MainWindow.hpp"
#include "Training_mode.hpp"
#include "WelcomeWindow.hpp"
#include "common_types.h"
#include "intro_window.hpp"
#include "progressbar.hpp"
int main(int argc, char *argv[])
{
  qRegisterMetaType<class fsr_data>("fsr_data");
  QApplication a(argc, argv);
  MainWindow w0;
  QPixmap pixmap("/Users/luca/Downloads/GaitLogo.png");
  QSplashScreen splash(pixmap);
  splash.show();
  a.processEvents();
  splash.finish(&w0);
  w0.show();
  a.exec();
  return 0;
}
