#include "main_window.h"
#include "chart.h"

#include "chart_view.h"

#include <QCheckBox>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QLineEdit>
#include <QLineSeries>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow()
    : m_chart(new Chart()),
      m_chart_view(new ChartView(m_chart, this)),
      m_series_box_layout(new QHBoxLayout(this)),
      m_saved_data_le(new QLineEdit(this))
{
  m_chart->setTitle("data visualization");

  auto *selectFileBtn = new QPushButton("...", this);
  connect(selectFileBtn, &QPushButton::pressed, this,
          &MainWindow::onFileSelectPressed);

  auto *loadFileBtn = new QPushButton("Load", this);
  connect(loadFileBtn, &QPushButton::pressed, this,
          &MainWindow::onFileLoadPressed);

  auto *dataSelectHL = new QHBoxLayout(this);
  dataSelectHL->addWidget(selectFileBtn);
  dataSelectHL->addWidget(m_saved_data_le);
  dataSelectHL->addWidget(loadFileBtn);

  auto *vLayout = new QVBoxLayout(this);
  vLayout->addLayout(dataSelectHL);
  vLayout->addLayout(m_series_box_layout);
  vLayout->addWidget(m_chart_view);

  auto *centralW = new QWidget(this);
  centralW->setLayout(vLayout);
  setCentralWidget(centralW);
}

void MainWindow::onFileSelectPressed()
{
  QString filename = QFileDialog::getOpenFileName(
      this, "Open Json Data", QDir::currentPath() + "/savedata",
      "All files (*.*) ;; Json files (*.json *.rtf)");
  m_saved_data_le->setText(QDir().relativeFilePath(filename));
}

void MainWindow::onFileLoadPressed()
{
  auto dataFile = QFile(m_saved_data_le->text());

  if (!dataFile.open(QFile::ReadOnly)) {
    QMessageBox().critical(0, "File Error", "Data file does not exist");
    return;
  }

  auto jsonDoc = QJsonDocument::fromJson(dataFile.readAll());

  QJsonObject root = jsonDoc.object();

  auto timepoints = root.keys();

  auto seriesNames = root[timepoints.first()].toObject().keys();

  for (auto timepointStr : timepoints) {
    auto timepoint = timepointStr.toDouble();
    auto tpData = root[timepointStr].toObject();
    for (auto seriesStr : seriesNames) {
      auto points = tpData[seriesStr].toArray();
      auto *series_x =
          m_chart->getSeries((seriesStr + "-X").toStdString().c_str());
      series_x->append({timepoint, points[0].toDouble()});

      auto *series_y =
          m_chart->getSeries((seriesStr + "-Y").toStdString().c_str());
      series_y->append({timepoint, points[1].toDouble()});

      auto *series_z =
          m_chart->getSeries((seriesStr + "-Z").toStdString().c_str());
      series_z->append({timepoint, points[2].toDouble()});
    }
  }

  for (const auto &seriesStr : seriesNames) {
    // Create 3 boxes to disable/enable the series.
    auto *box_x = new QCheckBox(seriesStr + "-X", this);
    box_x->setChecked(true);
    auto *series_x =
        m_chart->getSeries((seriesStr + "-X").toStdString().c_str());
    connect(box_x, &QCheckBox::stateChanged, series_x,
            &QLineSeries::setVisible);

    auto *box_y = new QCheckBox(seriesStr + "-Y", this);
    box_y->setChecked(true);
    auto *series_y =
        m_chart->getSeries((seriesStr + "-Y").toStdString().c_str());
    connect(box_y, &QCheckBox::stateChanged, series_y,
            &QLineSeries::setVisible);

    auto *box_z = new QCheckBox(seriesStr + "-Z", this);
    box_z->setChecked(true);
    auto *series_z =
        m_chart->getSeries((seriesStr + "-Z").toStdString().c_str());
    connect(box_z, &QCheckBox::stateChanged, series_z,
            &QLineSeries::setVisible);

    auto *vl = new QVBoxLayout(this);
    vl->addWidget(box_x);
    vl->addWidget(box_y);
    vl->addWidget(box_z);

    m_series_box_layout->addLayout(vl);
  }

  m_chart_view->adjustXAxis();
  m_chart_view->adjustYAxis();
}