#include "chart_view.h"

#include <QDebug>
#include <QLineSeries>
#include <algorithm>
#include <cmath>

QRectF seriesRect(QChart *chart, QAbstractSeries *series = nullptr)
{
  auto inScene = chart->plotArea();
  auto inChart = chart->mapFromScene(inScene);
  auto inChartRect = inChart.boundingRect();
  auto inItem1 = chart->mapToValue(inChartRect.topLeft(), series);
  auto inItem2 = chart->mapToValue(inChartRect.bottomRight(), series);
  return QRectF(inItem1, inItem2).normalized();
}

std::pair<qreal, qreal> yMinMax(QXYSeries *series, const QRectF &rect)
{
  // NOTE: If this turns out to be too inefficient, we can avoid this copy.
  auto const points = series->pointsVector();

  auto lowIt =
      std::lower_bound(points.begin(), points.end(), rect.left(),
                       [](const QPointF &a, qreal b) { return a.x() < b; });

  auto upIt =
      std::upper_bound(points.begin(), points.end(), rect.left(),
                       [](qreal a, const QPointF &b) { return a < b.x(); });

  if (lowIt != points.begin())
    lowIt = std::prev(lowIt);
  if (upIt != points.end())
    upIt = std::next(upIt);

  if (std::distance(lowIt, upIt) == 0)
    return {0, 1};

  auto minmax = std::minmax_element(
      lowIt, upIt, [](QPointF a, QPointF b) { return a.y() < b.y(); });
  return {minmax.first->y(), minmax.second->y()};
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
  m_last_mouse_pos = event->pos();
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
  if (!(event->buttons() & Qt::LeftButton))
    return;

  if (m_total_zoom_scale == 1)
    return;

  auto dPos = event->pos() - m_last_mouse_pos;
  chart()->scroll(-dPos.x(), 0);
  m_last_mouse_pos = event->pos();
}

void ChartView::wheelEvent(QWheelEvent *event)
{
  auto scalingFactor = event->angleDelta().y() / 80.f;
  if (scalingFactor < 0)
    scalingFactor = 1.0 / -scalingFactor;

  m_total_zoom_scale *= scalingFactor;
  if (m_total_zoom_scale < 1) {
    chart()->zoomReset();
    chart()->axisX()->setRange(
        0, static_cast<QXYSeries *>(chart()->series()[0])->points().back().x());
    m_total_zoom_scale = 1;
    return;
  }

  chart()->scroll(event->pos().x() - this->width() / 2, 0);
  chart()->zoom(scalingFactor);

  QRectF visibleRect = seriesRect(chart());
  QVector<qreal> visibleYs;

  for (auto *series : chart()->series()) {
    auto minmax = yMinMax(static_cast<QXYSeries *>(series), visibleRect);
    visibleYs.append(minmax.first);
    visibleYs.append(minmax.second);
  }

  auto minmax = std::minmax_element(visibleYs.begin(), visibleYs.end());

  chart()->axisY()->setRange(*minmax.first, *minmax.second);
}