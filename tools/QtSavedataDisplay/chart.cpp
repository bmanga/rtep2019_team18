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

  legend()->setAlignment(Qt::AlignBottom);
}

bool Chart::addSeries(const char *seriesName)
{
  // Cannot add the same series multiple times
  if (m_series.contains(seriesName))
    return false;

  auto *series = m_series[seriesName] = new QLineSeries(this);
  series->setName(seriesName);

  QChart::addSeries(series);

  series->attachAxis(m_axis_x);
  series->attachAxis(m_axis_y);

  return true;
}

QLineSeries *Chart::getSeries(const char *seriesName)
{
  addSeries(seriesName);
  return m_series[seriesName];
}
