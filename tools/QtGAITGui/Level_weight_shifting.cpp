#include "Level_weight_shifting.hpp"
#include <QDebug>
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
