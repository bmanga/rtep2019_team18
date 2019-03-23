#ifndef progressbar_hpp
#define progressbar_hpp

#include <stdio.h>
#include <QProgressBar>
#include <QWidget>

/**
 * Widget which displays a the current fill state of the Engine's internal
 * buffer, and the current play/record position within that buffer.
 */
class ProgressBar : public QProgressBar {
  Q_OBJECT

 public:
  explicit ProgressBar(QProgressBar *parent = 0);
  ~ProgressBar();

  void reset();
  void paintEvent(QPaintEvent *event) override;

 public slots:
  void bufferLengthChanged(float length);
  void recordPositionChanged(float recordPosition);
  void playPositionChanged(float playPosition);
  void windowChanged(float position, float length);

 private:
  float m_bufferLength;
  float m_recordPosition;
  float m_playPosition;
  float m_windowPosition;
  float m_windowLength;
};

#endif /* progressbar_hpp */
