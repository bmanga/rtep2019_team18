#ifndef Level_weight_shifting_hpp
#define Level_weight_shifting_hpp

#include <stdio.h>
#include <QJsonObject>
#include <QObject>
#include <QTimer>
#include <chrono>

class ProgressBar;

struct Target {
  float low;
  float high;
};

class LevelWS : public QObject {
  Q_OBJECT
 public:
  LevelWS(ProgressBar *left, ProgressBar *right);
  void setLvlRequirements(Target left,
                          Target right,
                          std::chrono::seconds timeRequirement);
  void loadJsonFile(QString file);
 public slots:
  void onLeftFSRChanged(bool onTarget);
  void onRightFSRChanged(bool onTarget);

  void start();

  void runLevel();

 private:
  void levelComplete();

 private:
  void checkTgtStatus();

 private:
  QJsonObject levelsRoot;
  QString currentLevel;
  QTimer m_timer;

  ProgressBar *m_leftBar;
  ProgressBar *m_rightBar;

  Target m_tgtLeft;
  Target m_tgtRight;
  std::chrono::seconds m_timeRequirement;

  bool m_leftOnTgt = false;
  bool m_rightOnTgt = false;
};
#endif /* Level_weight_shifting_hpp */
