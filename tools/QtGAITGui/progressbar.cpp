#include "progressbar.hpp"
#include <QDebug>
#include <QPainter>
#include <QProgressBar>
#include <QtWidgets>
#include <iostream>

ProgressBar::ProgressBar(QWidget *parent)
    : QProgressBar(parent),
      m_recordPosition(0),
      m_windowPosition(0),
      m_windowLength(0)
{

  // setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

  this->setTextVisible(false);
  this->show();

  this->setMaximum(10);
  max = 10;
  this->setMinimum(0);
  this->setValue(0);

  this->setOrientation(Qt::Vertical);
}

ProgressBar::~ProgressBar() {}

void ProgressBar::setTarget(float lower, float upper)
{
  m_targetLow = lower;
  m_targetHigh = upper;
}

void ProgressBar::checkStatus()
{
  bool posOnTarget = isPositionOnTarget(this->value());
  if (posOnTarget && !m_prevOnTarget) {
    emit onTarget(true);
  }
  else if (!posOnTarget && m_prevOnTarget) {
    emit onTarget(false);
  }
  m_prevOnTarget = posOnTarget;
}

bool ProgressBar::isPositionOnTarget(float val) const
{
  // printf("Maximum is: %d", this->maximum());
  return val >= m_targetLow * this->maximum() &&
         val <= m_targetHigh * this->maximum();
}

void ProgressBar::paintEvent(QPaintEvent *event)
{
  QColor new_green(0, 180, 0);
  QColor new_yellow(232, 220, 58);
  QColor new_red(188, 37, 37);
  auto color =
      m_prevOnTarget
          ? new_green
          : interpolate3(this->value() / (float)this->maximum(), new_red,
                         (this->m_targetHigh + this->m_targetLow) / 2,
                         new_yellow, new_red);

  QString sh = QString(R"(QProgressBar {
                       background: #80c0cbd1;
                       border: 0px solid black;
                       text-align: top;
                       padding: 0px;
                       border-bottom-right-radius: 7px;
                       border-bottom-left-radius: 7px;
                       width: 15px;
                       }
                       
                       QProgressBar::chunk {
                       background: %1;
                         border-bottom-right-radius: 0px;
                         border-bottom-left-radius: 0px;
                       border: 0 solid black;
                       })")
                   .arg(color.name());

  this->setStyleSheet(sh);

  QPainter painter_fill(this);
  QColor targetColor(0, 180, 0);
  QPen pen_box;
  pen_box.setWidth(8);
  pen_box.setBrush(Qt::black);
  QRect box = rect();
  box.setRect(
      -5, this->height() - ((this->m_targetHigh) * (this->height() - 4)), 60,
      (this->m_targetHigh - this->m_targetLow) * (this->height() - 4));
  painter_fill.fillRect(box, targetColor);

  QProgressBar::paintEvent(event);
  {
    QPainter painter_border(this);
    QPen pen_box;
    pen_box.setWidth(8);
    pen_box.setBrush(Qt::black);
    QRect box = rect();
    box.setRect(-5, this->height() - 4, 60, 75);
    box.setRect(
        -5, this->height() - ((this->m_targetHigh) * (this->height() - 4)), 60,
        (this->m_targetHigh - this->m_targetLow) * (this->height() - 4));
    // std::cout<<(this->m_targetHigh-this->m_targetHigh)*(this->height()-4);
    painter_border.setPen(pen_box);
    painter_border.drawRect(box);
  }
}

void ProgressBar::recordPositionChanged(float recordPosition)
{
  Q_ASSERT(recordPosition >= 0);
  this->m_recordPosition = recordPosition;
  this->repaint();
}

void ProgressBar::playPositionChanged(float playPosition)
{
  this->setValue(playPosition * 10);
  /*if (playPosition * 10 >= max) {
    this->setMaximum(playPosition * 10);
    max = playPosition * 10;
  }*/
  checkStatus();
}

void ProgressBar::windowChanged(float position, float length)
{
  Q_ASSERT(position >= 0);
  Q_ASSERT(position + length <= this->maximum());
  this->m_windowPosition = position;
  this->m_windowLength = length;
  this->repaint();
}

QColor ProgressBar::interpolate2(float pos, QColor initial, QColor end) const
{
  int red = (int)((1 - pos) * initial.red() + (pos)*end.red());
  int green = (int)((1 - pos) * initial.green() + (pos)*end.green());
  int blue = (int)((1 - pos) * initial.blue() + (pos)*end.blue());
  return {red, green, blue};
}

QColor ProgressBar::interpolate3(float pos,
                                 QColor start,
                                 float middlePos,
                                 QColor middle,
                                 QColor end) const
{
  if (pos < middlePos)
    return interpolate2(pos / middlePos, start, middle);
  return interpolate2((pos - middlePos) / (1 - middlePos), middle, end);
}

void ProgressBar::setMaxValue(double calibrationMax)
{
  printf("Maximum: %.3f", calibrationMax);
  this->setMaximum(int(calibrationMax) * 10);
}
