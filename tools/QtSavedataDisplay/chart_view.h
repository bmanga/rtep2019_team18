#ifndef RTEP_TEAM18_CHART_VIEW_H
#define RTEP_TEAM18_CHART_VIEW_H

#include <QtCharts/QChartView>

using namespace QtCharts;

class ChartView : public QChartView {
 public:
  using QChartView::QChartView;

  void adjustXAxis();
  void adjustYAxis();

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  QPoint m_last_mouse_pos;
  qreal m_total_zoom_scale = 1;
};
#endif  // RTEP_TEAM18_CHART_VIEW_H
