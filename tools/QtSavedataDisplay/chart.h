#ifndef RTEP_TEAM18_CHART_H
#define RTEP_TEAM18_CHART_H

#include <QGestureEvent>
#include <QMap>
#include <QString>
#include <QtCharts/QChart>

#include <QList>

using namespace QtCharts;

namespace QtCharts {
class QValueAxis;
class QLineSeries;
}  // namespace QtCharts

class Chart : public QChart {
 public:
  Chart();
  void addSeries(const char *seriesName, const QList<QPointF> &datapoints);

 private:
  QMap<QString, QLineSeries *> m_series;

  QValueAxis *m_axis_x;
  QValueAxis *m_axis_y;
};

#endif  // RTEP_TEAM18_CHART_H
