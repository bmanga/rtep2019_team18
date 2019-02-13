/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include "telemetry/client.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_time_start(std::chrono::system_clock::now()),
      m_series_x(0),
      m_series_y(0),
      m_series_z(0),
      m_axisX(new QValueAxis()),
      m_axisY(new QValueAxis()),
      m_step(0),
      m_x(5),
      m_y(1)
{
  // QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
  // m_timer.setInterval(500);

  QPen pen_x;  //
  pen_x.setWidth(3);
  pen_x.setBrush(Qt::red);

  QPen pen_y;  //
  pen_y.setWidth(3);
  pen_y.setBrush(Qt::green);

  QPen pen_z;  //
  pen_z.setWidth(3);
  pen_z.setBrush(Qt::blue);

  m_series_x = new QSplineSeries(this);
  m_series_x->setName("X-axis");
  m_series_x->setPen(pen_x);

  m_series_y = new QSplineSeries(this);
  m_series_y->setName("Y-axis");
  m_series_y->setPen(pen_y);

  m_series_z = new QSplineSeries(this);
  m_series_z->setName("Z-axis");
  m_series_z->setPen(pen_z);

  m_series_x->append(0, 0);

  m_series_y->append(0, 0);

  m_series_z->append(0, 0);

  addSeries(m_series_x);
  addSeries(m_series_y);
  addSeries(m_series_z);

  addAxis(m_axisX, Qt::AlignBottom);
  addAxis(m_axisY, Qt::AlignLeft);
  m_series_x->attachAxis(m_axisX);
  m_series_x->attachAxis(m_axisY);

  m_series_y->attachAxis(m_axisX);
  m_series_y->attachAxis(m_axisY);

  m_series_z->attachAxis(m_axisX);
  m_series_z->attachAxis(m_axisY);

  m_axisX->setTickCount(5);
  m_axisX->setRange(0, 10);
  m_axisY->setRange(-2, 2);

  m_timer.start();  // maybe remove
  m_client.set_message_handler(
      [this](const void *data, long len) { this->on_message(data, len); });
  m_client.connect_to("ws://192.168.5.1:9006");
  m_client.run_on_thread();
}

Chart::~Chart() {}

void Chart::handleTimeout()
{
  qreal x = plotArea().width() / m_axisX->tickCount();
  qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
  m_x += y;
  m_y = QRandomGenerator::global()->bounded(5) - 2.5;
  m_series_x->append(m_x, m_y);
  m_series_y->append(m_x, m_y + 10);
  m_series_z->append(m_x, m_y + 20);
  if (m_x >= m_axisX->max())
    axisX()->setRange(m_x - 10, m_x);
  if (m_x == 100)
    m_timer.stop();
  legend()->setVisible(true);
  legend()->setAlignment(Qt::AlignBottom);
}

struct sensors_data {
  float ax, ay, az;
  float gx, gy, gz;
};

void Chart::on_message(const void *d, long len)
{
  sensors_data data;
  memcpy(&data, d, len);
  auto x = std::chrono::system_clock::now() - m_time_start;
  double x_sec =
      std::chrono::duration_cast<std::chrono::milliseconds>(x).count() / 1000.0;

  m_series_x->append(x_sec, data.gx);
  m_series_y->append(x_sec, data.gy);
  m_series_z->append(x_sec, data.gz);
  if (x_sec >= m_axisX->max())
    axisX()->setRange(x_sec - 10, x_sec);

  legend()->setVisible(true);
  legend()->setAlignment(Qt::AlignBottom);
}
