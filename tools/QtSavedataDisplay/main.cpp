#include <QApplication>
#include "main_window.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow window;
  window.resize(700, 700);
  window.show();
  return a.exec();
}
