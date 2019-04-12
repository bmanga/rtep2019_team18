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

  QMainWindow w0, w1, w2, w3, w4, w5;
  w0.setCentralWidget(new WelcomeWindow());
  w1.setCentralWidget(new IntroWindow());
  w2.setCentralWidget(new CalibrateWindow());
  w3.setCentralWidget(t1);
  w4.setCentralWidget(t2);
  w5.setCentralWidget(new FinalWindow());
  QPixmap pixmap("/Users/luca/Downloads/GaitLogo.png");
  QSplashScreen splash(pixmap);
  splash.show();
  a.processEvents();
  splash.finish(&w0);
  w0.show();
  w1.show();
  w2.show();
  w3.show();
  w4.show();
  w5.show();
  a.exec();
  return 0;
}
