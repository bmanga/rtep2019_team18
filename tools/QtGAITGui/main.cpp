#include <QSplashScreen>
#include <QtWidgets/QApplication>
#include "CalibrateWindow.hpp"
#include "CircleWidget.hpp"
#include "FinalWindow.hpp"
#include "MainWindow.hpp"
#include "Training_mode.hpp"
#include "WelcomeWindow.hpp"
#include "intro_window.hpp"
#include "progressbar.hpp"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  auto t1 = new TrainingMode<ProgressBar>(R"(
                                          <html>
                                          <center><b>Welcome to the Weight Shifting exercise!</b> <\center>
                                          <br>
                                          <br>
                                          Shift your weight from one foot to the other to reach the target levels shown on each bar
                                          <br>
                                          
                                          </html>)");
  auto t2 = new TrainingMode<CircleWidget>(R"(
                                           <html>
                                           <center><b>Welcome to the Calf Pushes exercise!</b> <\center>
                                           <br>
                                           <br>
                                           Shift your weight from heel to toes to  reach the target levels shown on each bar
                                           <br>
                                           </html>)");

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
