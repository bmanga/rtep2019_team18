//
//  CircleWidget.cpp
//  qt-imu-visualizer
//
//  Created by Luca Rosalia on 20/03/2019.
//

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
  // painter.setRenderHint(QPainter::Antialiasing, antialiased);
  painter.translate(width() / 2, height() / 2);
  painter.setPen(QPen(Qt::black, 3));
  painter.drawEllipse(QRect(-diameter / 2, -diameter / 2, diameter, diameter));

  //  for (int diameter = 0; diameter < 256; diameter += 9) {
  //    int delta = abs((frameNo % 128) - diameter / 2);
  //    int alpha = 255 - (delta * delta) / 4 - diameter;
  //    if (alpha > 0) {
  //      painter.setPen(QPen(QColor(0, diameter / 2, 127, alpha), 3));
  //
  //      if (floatBased)
  //        painter.drawEllipse(QRectF(-diameter / 2.0, -diameter / 2.0,
  //        diameter, diameter));
  //      else
  //        painter.drawEllipse(QRect(-diameter / 2, -diameter / 2, diameter,
  //        diameter));
  //    }
  //  }
}
