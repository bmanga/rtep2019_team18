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
#include <QJsonArray>
#include <QJsonObject>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QDebug>
#include <cassert>
#include "telemetry/client.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_series_x(0),
      m_series_y(0),
      m_series_z(0),
      m_axisX(new QValueAxis()),
      m_axisY(new QValueAxis())
{
  QPen pen_x;  //
  pen_x.setWidth(3);
  pen_x.setBrush(Qt::red);

  QPen pen_y;  //
  pen_y.setWidth(3);
  pen_y.setBrush(Qt::green);

  QPen pen_z;  //
  pen_z.setWidth(3);
  pen_z.setBrush(Qt::blue);

  m_series_x = new QLineSeries(this);
  m_series_x->setName("X-axis");
  m_series_x->setPen(pen_x);

  m_series_y = new QLineSeries(this);
  m_series_y->setName("Y-axis");
  m_series_y->setPen(pen_y);

  m_series_z = new QLineSeries(this);
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

  m_series_x->setUseOpenGL(true);
  m_series_y->setUseOpenGL(true);
  m_series_z->setUseOpenGL(true);
}

void Chart::saveToJson(QJsonObject &root, const char *groupName)
{
  assert(m_series_x->count() == m_series_y->count() &&
         m_series_y->count() == m_series_z->count());

  QJsonArray series;
  for (int j = 0, max = m_series_x->count(); j < max; ++j) {
    QJsonArray data(
        {m_series_x->at(j).y(), m_series_y->at(j).y(), m_series_z->at(j).y()});

    auto currentTimepoint =
        root[QString::number(m_series_x->at(j).x())].toObject();
    currentTimepoint[groupName] = data;

    root[QString::number(m_series_x->at(j).x())] = currentTimepoint;
  }
}

Chart::~Chart() {}

qreal Chart::getXAxisMax() const
{
  return m_axisX->max();
}
