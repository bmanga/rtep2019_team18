#ifndef progressbar_hpp
#define progressbar_hpp

#include <stdio.h>
#include <QColor>
#include <QProgressBar>
#include <QWidget>
#include "MainWindow.hpp"

/**
 * Widget which displays a the current fill state of the Engine's internal
 * buffer, and the current play/record position within that buffer.
 */
class ProgressBar : public QProgressBar {
  Q_OBJECT

 public:
  explicit ProgressBar(QWidget *parent = 0);
  ~ProgressBar();

  void reset();
  void paintEvent(QPaintEvent *event) override;

  void setMaxValue(double calibrationMax);

  QColor interpolate2(float pos, QColor start, QColor end) const;
  QColor interpolate3(float pos,
                      QColor start,
                      float middlePos,
                      QColor middle,
                      QColor end) const;

 public slots:
  void recordPositionChanged(float recordPosition);
  void playPositionChanged(float playPosition);
  void windowChanged(float position, float length);
  void setTarget(float lower, float upper);
  void checkStatus();

  void onNewFSRData(fsr_data packet)
  {
    playPositionChanged(packet.toe + packet.heel);
  }

 signals:
  void onTarget(bool);

 private:
  bool isPositionOnTarget(float val) const;

 private:
  float m_recordPosition;
  float m_windowPosition;
  float m_windowLength;
  float m_targetLow;
  float m_targetHigh;

  float max;

  bool m_prevOnTarget = false;
};

#endif /* progressbar_hpp */
