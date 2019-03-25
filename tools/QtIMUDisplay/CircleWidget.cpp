#include "CircleWidget.hpp"

#include <QPainter>

#include <stdlib.h>

CircleWidget::CircleWidget(QWidget *parent) : QWidget(parent)
{
  floatBased = false;
  antialiased = false;
  frameNo = 0;
  diameter = 0;
  setBackgroundRole(QPalette::Base);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CircleWidget::setDiameter(int d)
{
  this->diameter = d;
  this->repaint();
}

void CircleWidget::setFloatBased(bool floatBased)
{
  this->floatBased = floatBased;
  update();
}

void CircleWidget::setAntialiased(bool antialiased)
{
  this->antialiased = antialiased;
  update();
}

QSize CircleWidget::minimumSizeHint() const
{
  return QSize(50, 50);
}

QSize CircleWidget::sizeHint() const
{
  return QSize(180, 180);
}

void CircleWidget::nextAnimationFrame()
{
  ++frameNo;
  update();
}

void CircleWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, antialiased);
  QColor targetColor(0, 180, 0);
  painter.translate(width() / 2, height() / 2);
  painter.setPen(QPen(targetColor, 5));
  painter.drawEllipse(QRect(-this->diameter / 2, -this->diameter / 2,
                            this->diameter, this->diameter));
  painter.setPen(QPen(Qt::green, 3));
  painter.drawEllipse(QRect(-50, -50, 100, 100));  // 100 will be target
}
