#ifndef RTEP_TEAM18_MAIN_WINDOW_H
#define RTEP_TEAM18_MAIN_WINDOW_H

#include <QMainWindow>

class Chart;
class ChartView;

class QHBoxLayout;
class QLineEdit;

class MainWindow : public QMainWindow {
 public:
  MainWindow();

 public slots:
  void onFileSelectPressed();
  void onFileLoadPressed();

 private:
  Chart *m_chart;
  ChartView *m_chart_view;
  QHBoxLayout *m_series_box_layout;
  QLineEdit *m_saved_data_le;
};

#endif  // RTEP_TEAM18_MAIN_WINDOW_H
