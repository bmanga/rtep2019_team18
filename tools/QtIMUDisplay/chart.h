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

#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//![1]
class Chart : public QChart {
  Q_OBJECT
 public:
  Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
  virtual ~Chart();  // Chart is an instance - each will contain 3 series
                     // (variables below)

  QSplineSeries *m_series_x;
  QSplineSeries *m_series_y;
  QSplineSeries
      *m_series_z;  // will have 3 series (x,y,z) for each Chart instance

  qreal getXAxisMax() const;

 private:
  QStringList m_titles;
  QValueAxis *m_axisX;
  QValueAxis *m_axisY;
};
//![1]

#endif /* CHART_H */
