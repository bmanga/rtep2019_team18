#ifndef Level_weight_shifting_hpp
#define Level_weight_shifting_hpp

#include <stdio.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <chrono>
#include "TargetBase.h"

template <class>
class TrainingMode;

template <class TargetT>
class LevelWS : public QObject {
 public:
  LevelWS(TrainingMode<TargetT> *parent,
          TargetT *left,
          TargetT *right,
          QLabel *label)
      : m_parent(parent), m_leftBar(left), m_rightBar(right), m_label(label)
  {
    connect(left, &TargetT::onTarget, this, &LevelWS::onLeftFSRChanged);
    connect(right, &TargetT::onTarget, this, &LevelWS::onRightFSRChanged);

    m_timer.setSingleShot(true);

    connect(&m_timer, &QTimer::timeout, this, &LevelWS::levelComplete);
  }

  void setLvlRequirements(Target left,
                          Target right,
                          std::chrono::seconds timeRequirement)
  {
    m_leftBar->setTarget(left);
    m_rightBar->setTarget(right);
    m_timeRequirement = timeRequirement;
  }

  void loadJsonFile(QString file)
  {
    QFile dataFile(file);

    if (!dataFile.open(QFile::ReadOnly)) {
      QMessageBox().critical(0, "File Error", "Data file does not exist");
      return;
    }

    auto jsonDoc = QJsonDocument::fromJson(dataFile.readAll());

    levelsRoot = jsonDoc.object();
  }

 public slots:
  void onLeftFSRChanged(bool onTarget)
  {
    m_leftOnTgt = onTarget;
    checkTgtStatus();
  }

  void onRightFSRChanged(bool onTarget)
  {
    m_rightOnTgt = onTarget;
    checkTgtStatus();
  }

  void levelComplete()
  {
    auto levelIdx = levelsRoot.keys().indexOf(currentLevel);
    if (levelIdx == levelsRoot.keys().size() - 1) {
      // This was the last level
      m_parent->emitWindowDone();
      return;
    }
    currentLevel = levelsRoot.keys()[levelIdx + 1];
    runLevel();
  }

  void start()
  {
    currentLevel = levelsRoot.keys()[0];

    runLevel();
  }

  void runLevel()
  {
    m_label->setText(currentLevel);
    auto levelData = levelsRoot[currentLevel].toObject();

    long duration = levelData["Time"].toDouble();

    auto leftArray = levelData["Left"].toArray();
    auto rightArray = levelData["Right"].toArray();

    setLvlRequirements({leftArray[0].toDouble(), leftArray[1].toDouble()},
                       {rightArray[0].toDouble(), rightArray[1].toDouble()},
                       std::chrono::seconds(duration));

    m_timer.start(m_timeRequirement);
  }

 private:
  void checkTgtStatus()
  {
    if (m_rightOnTgt && m_leftOnTgt) {
      m_timer.start(m_timeRequirement);
    }
    else {
      m_timer.stop();
    }
  }

 private:
  QJsonObject levelsRoot;
  QString currentLevel;
  QTimer m_timer;

  TargetT *m_leftBar;
  TargetT *m_rightBar;

  QLabel *m_label;

  TrainingMode<TargetT> *m_parent;

  Target m_tgtLeft;
  Target m_tgtRight;
  std::chrono::seconds m_timeRequirement;

  bool m_leftOnTgt = false;
  bool m_rightOnTgt = false;
};
#endif /* Level_weight_shifting_hpp */
