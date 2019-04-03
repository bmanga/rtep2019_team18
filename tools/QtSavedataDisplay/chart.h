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
  bool addSeries(const char *seriesName);
  QLineSeries *getSeries(const char *seriesName);

 private:
  QMap<QString, QLineSeries *> m_series;

  QValueAxis *m_axis_x;
  QValueAxis *m_axis_y;
};

#endif  // RTEP_TEAM18_CHART_H
