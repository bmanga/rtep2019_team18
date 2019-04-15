#include "Level_weight_shifting.hpp"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QLineEdit>
#include <chrono>
#include "progressbar.hpp"

LevelWS::LevelWS(ProgressBar *left, ProgressBar *right)
    : m_leftBar(left), m_rightBar(right)
{
  connect(left, &ProgressBar::onTarget, this, &LevelWS::onLeftFSRChanged);
  connect(right, &ProgressBar::onTarget, this, &LevelWS::onRightFSRChanged);

  m_timer.setSingleShot(true);

  connect(&m_timer, SIGNAL(timeout()), this, SIGNAL(levelComplete()));
  connect(this, &LevelWS::levelComplete, []() { qDebug() << "success"; });
}

void LevelWS::onLeftFSRChanged(bool onTarget)
{
  m_leftOnTgt = onTarget;
  checkTgtStatus();
}

void LevelWS::onRightFSRChanged(bool onTarget)
{
  m_rightOnTgt = onTarget;
  checkTgtStatus();
}

void LevelWS::setLvlRequirements(Target left,
                                 Target right,
                                 std::chrono::seconds timeRequirement)
{
  m_leftBar->setTarget(left.low, left.high);
  m_rightBar->setTarget(right.low, right.high);
  m_timeRequirement = timeRequirement;
}

void LevelWS::checkTgtStatus()
{
  if (m_rightOnTgt && m_leftOnTgt) {
    m_timer.start(m_timeRequirement);
  }
  else {
    m_timer.stop();
  }
}

void LevelWS::loadJsonFile(QString file)
{
  QFile dataFile(file);

  auto jsonDoc = QJsonDocument::fromJson(dataFile.readAll());

  levelsRoot = jsonDoc.object();
}

void LevelWS::start()
{
  currentLevel = levelsRoot.keys()[0];

  runLevel();
}
void LevelWS::runLevel()
{
  auto levelData = levelsRoot[currentLevel].toObject();

  long duration = levelData["Time"].toDouble();

  auto leftArray = levelData["Left"].toArray();
  auto rightArray = levelData["RIght"].toArray();

  setLvlRequirements({leftArray[0].toDouble(), leftArray[1].toDouble()}, ,
                     {rightArray[0].toDouble(), rightArray[1].toDouble()},
                     std::chrono::seconds(duration));

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
}
