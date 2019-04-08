#ifndef CircleWidget_hpp
#define CircleWidget_hpp

#include <stdio.h>

#include <QWidget>

class CircleWidget : public QWidget {
  Q_OBJECT

 public:
  CircleWidget(QWidget *parent = 0);

  void paintEvent(QPaintEvent *event) override;
  QColor interpolate2(float pos, QColor start, QColor end) const;  // NEW
  QColor interpolate3(float pos,
                      QColor start,
                      float middlePos,
                      QColor middle,
                      QColor end) const;  // NEW
  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

 public slots:
  void setDiameter(float d);
  float getDiameter();
  void setTarget(float lower, float upper);  // NEW
  void checkStatus();                        // NEW

 private:
  bool floatBased;
  bool antialiased;
  float diameter;
  float max_diameter;
  float m_targetLow = 0.3;   // NEW
  float m_targetHigh = 0.5;  // NEW
  bool m_prevOnTarget = false;
  bool isPositionOnTarget(float val) const;  // NEW

 signals:
  void onTarget(bool);
};

#endif /* CircleWidget_hpp */
