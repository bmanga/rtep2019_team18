#include "main_window.h"
#include "chart.h"

#include "chart_view.h"

MainWindow::MainWindow() : m_chart(new Chart())
{
  m_chart->setTitle("data visualization");

  auto *chartView = new ChartView(m_chart, this);

  setCentralWidget(chartView);
}