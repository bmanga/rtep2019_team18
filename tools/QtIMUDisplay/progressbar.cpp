#include "progressbar.hpp"
#include <QPainter>
#include <QProgressBar>
#include <QtWidgets>

ProgressBar::ProgressBar(QProgressBar *parent)
    : QProgressBar(parent),
      m_bufferLength(100),
      m_recordPosition(0),
      m_playPosition(0),
      m_windowPosition(0),
      m_windowLength(0)
{
  // setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  setFixedWidth(50);
  setFixedHeight(400);
}

ProgressBar::~ProgressBar() {}

void ProgressBar::reset()
{
  m_bufferLength = 0;
  m_recordPosition = 0;
  m_playPosition = 0;
  m_windowPosition = 0;
  m_windowLength = 0;
  update();
}

void ProgressBar::paintEvent(QPaintEvent * /*event*/)
{
  QPainter painter(this);
  const qreal play = qreal(m_playPosition) / m_bufferLength;
  QColor bufferColor((1 - play) * 255, (play)*255, 20);  // RGB
  QColor targetColor(0, 180, 0);
  QColor windowColor(255, 255, 0);

  painter.fillRect(rect(), Qt::lightGray);

  if (m_bufferLength) {
    QRect bar = rect();
    const qreal play = qreal(m_playPosition) / m_bufferLength;
    bar.setBottom(0 + (1 - play) * 400);
    const qreal record = qreal(m_recordPosition) / m_bufferLength;
    bar.setTop(0 + (1 - record) * 400);
    painter.fillRect(bar, bufferColor);

    QPen pen_box;
    pen_box.setWidth(8);
    pen_box.setBrush(Qt::black);
    QRect box = rect();
    box.setRect(-5, 100, 60, 75);
    painter.fillRect(box, targetColor);
    painter.setPen(pen_box);
    painter.drawRect(box);

    QRect window = rect();
    const qreal windowLeft = qreal(m_windowPosition) / m_bufferLength;
    window.setLeft(rect().left() + windowLeft * rect().width());

    const qreal windowWidth = qreal(m_windowLength) / m_bufferLength;
    window.setWidth(windowWidth * rect().width());
    painter.fillRect(window, windowColor);
  }
}

void ProgressBar::bufferLengthChanged(float bufferSize)
{
  m_bufferLength = bufferSize;
  m_recordPosition = 0;
  m_playPosition = 0;
  m_windowPosition = 0;
  m_windowLength = 0;
  repaint();
}

void ProgressBar::recordPositionChanged(float recordPosition)
{
  Q_ASSERT(recordPosition >= 0);
  Q_ASSERT(recordPosition <= m_bufferLength);
  this->m_recordPosition = recordPosition;
  this->repaint();
}

void ProgressBar::playPositionChanged(float playPosition)
{
  Q_ASSERT(playPosition >= 0);
  Q_ASSERT(playPosition <= m_bufferLength);
  this->m_playPosition = playPosition;
  this->repaint();
}

void ProgressBar::windowChanged(float position, float length)
{
  Q_ASSERT(position >= 0);
  Q_ASSERT(position <= m_bufferLength);
  Q_ASSERT(position + length <= m_bufferLength);
  this->m_windowPosition = position;
  this->m_windowLength = length;
  this->repaint();
}
