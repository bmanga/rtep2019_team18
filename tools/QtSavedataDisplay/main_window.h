#ifndef RTEP_TEAM18_MAIN_WINDOW_H
#define RTEP_TEAM18_MAIN_WINDOW_H

#include <QMainWindow>

class Chart;

class MainWindow : public QMainWindow {
 public:
  MainWindow();

 private:
  Chart *m_chart;
};

#endif  // RTEP_TEAM18_MAIN_WINDOW_H
