#include "CircleWidget.hpp"

#include <stdlib.h>
#include <QPainter>
#include <iostream>

CircleWidget::CircleWidget(QWidget *parent) : QWidget(parent)
{
  floatBased = false;
  antialiased = true;
  diameter = 0;
  max_diameter = 10;
  setBackgroundRole(QPalette::Base);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CircleWidget::setDiameter(float d)
{
  this->diameter = d * 100;
  checkStatus();
  this->repaint();
}

float CircleWidget::getDiameter()
{
  return this->diameter;
}

void CircleWidget::setTarget(Target t)
{
  m_targetLow = t.low;
  m_targetHigh = t.high;
}

void CircleWidget::checkStatus()
{
  bool posOnTarget = isPositionOnTarget(this->getDiameter());

  if (posOnTarget && !m_prevOnTarget) {
    emit onTarget(true);
  }
  else if (!posOnTarget && m_prevOnTarget) {
    emit onTarget(false);
  }
  m_prevOnTarget = posOnTarget;
}

bool CircleWidget::isPositionOnTarget(float val) const
{
  return val >= m_targetLow * this->max_diameter + 10 &&
         val <= m_targetHigh * this->max_diameter +
                    10;  // max diam will (kinda) come from calibration
}

QSize CircleWidget::minimumSizeHint() const
{
  return QSize(50, 50);
}

QSize CircleWidget::sizeHint() const
{
  return QSize(800, 800);
}

void CircleWidget::paintEvent(QPaintEvent *)
{
  QColor targetColor(0, 180, 0, 255.02 / 2.0);
  QColor new_green(0, 180, 0);
  QColor new_yellow(232, 220, 58);
  QColor new_red(188, 37, 37);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, antialiased);
  painter.translate(width() / 2, height() / 2);
  float max = this->max_diameter;
  float d_outer = max * this->m_targetHigh;
  float d_inner = max * this->m_targetLow;
  float midline_target = (d_outer + d_inner + 20) / 2.0;
  float thickness_target = (d_outer - d_inner) / 2.0;
  painter.setPen(QPen(targetColor, thickness_target));
  painter.drawEllipse(QRect(-midline_target / 2.0, -midline_target / 2.0,
                            midline_target, midline_target));

  auto color =
      m_prevOnTarget
          ? new_green
          : interpolate3(this->getDiameter() / this->max_diameter, new_red,
                         (this->m_targetHigh + this->m_targetLow) / 2,
                         new_yellow, new_red);
  painter.setPen(QPen(color, 6));
  painter.drawEllipse(QRect(-this->getDiameter() / 2, -this->getDiameter() / 2,
                            this->getDiameter(), this->getDiameter()));
  painter.setPen(QPen(Qt::black, 5));
  painter.drawEllipse(QRect(-(d_outer + 10) / 2.0, -(d_outer + 10) / 2.0,
                            (d_outer + 10), (d_outer + 10)));
  painter.drawEllipse(QRect(-(d_inner + 10) / 2.0, -(d_inner + 10) / 2.0,
                            (d_inner + 10), (d_inner + 10)));
}

QColor CircleWidget::interpolate2(float pos, QColor initial, QColor end) const
{
  int red = (int)((1 - pos) * initial.red() + (pos)*end.red());
  int green = (int)((1 - pos) * initial.green() + (pos)*end.green());
  int blue = (int)((1 - pos) * initial.blue() + (pos)*end.blue());
  return {red, green, blue};
}

QColor CircleWidget::interpolate3(float pos,
                                  QColor start,
                                  float middlePos,
                                  QColor middle,
                                  QColor end) const
{
  if (pos < middlePos)
    return interpolate2(pos / middlePos, start, middle);
  return interpolate2((pos - middlePos) / (1 - middlePos), middle, end);
}

void CircleWidget::setMaxValue(double calibrationMax)
{
  this->max_diameter = calibrationMax * 100;
}
