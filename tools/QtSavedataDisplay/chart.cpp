#include "chart.h"

#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneWheelEvent>
#include <QLineSeries>
#include <QValueAxis>

Chart::Chart() : m_axis_x(new QValueAxis()), m_axis_y(new QValueAxis())
{
  grabGesture(Qt::PanGesture);
  grabGesture(Qt::SwipeGesture);

  addAxis(m_axis_x, Qt::AlignBottom);
  addAxis(m_axis_y, Qt::AlignLeft);
}

void Chart::addSeries(const char *seriesName, const QList<QPointF> &datapoints)
{
  // Cannot add the same series multiple times
  if (m_series.contains(seriesName))
    return;

  auto *series = m_series[seriesName] = new QLineSeries(this);
  series->setName(seriesName);

  series->append(datapoints);

  QChart::addSeries(series);

  series->attachAxis(m_axis_x);
  series->attachAxis(m_axis_y);
}
