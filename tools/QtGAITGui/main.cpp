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
<<<<<<< HEAD
  qRegisterMetaType<class fsr_packet>("fsr_packet");
  QApplication a(argc, argv);
  MainWindow w0;
=======
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

<<<<<<< HEAD
  QMainWindow w0, w1, w2, w3, w4, w5;
  w0.setCentralWidget(new WelcomeWindow());
  w1.setCentralWidget(new IntroWindow());
  w2.setCentralWidget(new CalibrateWindow());
  w3.setCentralWidget(t1);
  w4.setCentralWidget(t2);
  w5.setCentralWidget(new FinalWindow());
>>>>>>> Edited GUI, now works with realtime data from sensors.
=======
  MainWindow w0;
>>>>>>> qt gui: all windows in training mode are now connected
  QPixmap pixmap("/Users/luca/Downloads/GaitLogo.png");
  QSplashScreen splash(pixmap);
  splash.show();
  a.processEvents();
  splash.finish(&w0);
  w0.show();
<<<<<<< HEAD
<<<<<<< HEAD

=======
  w1.show();
  w2.show();
  w3.show();
  w4.show();
  w5.show();
>>>>>>> Edited GUI, now works with realtime data from sensors.
=======

>>>>>>> qt gui: all windows in training mode are now connected
  a.exec();
  return 0;
}
