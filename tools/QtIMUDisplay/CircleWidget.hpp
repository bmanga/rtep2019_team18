#ifndef CircleWidget_hpp
#define CircleWidget_hpp

#include <stdio.h>

#include <QWidget>

class CircleWidget : public QWidget {
  Q_OBJECT

 public:
  CircleWidget(QWidget *parent = 0);

  void setFloatBased(bool floatBased);
  void setAntialiased(bool antialiased);
  void setDiameter(int d);

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

 public slots:
  void nextAnimationFrame();

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  bool floatBased;
  bool antialiased;
  int frameNo;
  int diameter;
};

#endif /* CircleWidget_hpp */
