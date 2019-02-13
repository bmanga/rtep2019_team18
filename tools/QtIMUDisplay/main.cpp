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

#include <QCheckBox>
#include <QHBoxLayout>
#include <QSplineSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "chart.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QMainWindow window;
  Chart *chart_acc = new Chart;  // Chart for acceleration data
  chart_acc->setTitle("Acceleration data chart");
  chart_acc->legend()->hide();
  Chart *chart_gyr = new Chart;  // Chart for gyroscope data
  chart_gyr->setTitle("Gyroscope data chart");
  chart_gyr->legend()->hide();

  QCheckBox *Box1 = new QCheckBox("Axis X");
  Box1->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box1, &QCheckBox::stateChanged, chart_acc->m_series_x,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box1, &QCheckBox::stateChanged, chart_gyr->m_series_x,
                   &QAbstractSeries::setVisible);

  QCheckBox *Box2 = new QCheckBox("Axis Y");
  Box2->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box2, &QCheckBox::stateChanged, chart_acc->m_series_y,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box2, &QCheckBox::stateChanged, chart_gyr->m_series_y,
                   &QAbstractSeries::setVisible);

  QCheckBox *Box3 = new QCheckBox("Axis Z");
  Box3->setCheckState(Qt::CheckState::Checked);
  QObject::connect(Box3, &QCheckBox::stateChanged, chart_acc->m_series_z,
                   &QAbstractSeries::setVisible);
  QObject::connect(Box3, &QCheckBox::stateChanged, chart_gyr->m_series_z,
                   &QAbstractSeries::setVisible);

  QChartView chartView_1(chart_acc);
  QChartView chartView_2(chart_gyr);
  chartView_1.setRenderHint(QPainter::Antialiasing);
  chartView_2.setRenderHint(QPainter::Antialiasing);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(&chartView_1);
  layout->addWidget(&chartView_2);
  layout->addWidget(Box1);
  layout->addWidget(Box2);
  layout->addWidget(Box3);

  QWidget *charts = new QWidget();
  charts->setLayout(layout);
  window.setCentralWidget(charts);
  window.resize(700, 700);
  window.show();
  return a.exec();
}
