#ifndef FinalWindow_hpp
#define FinalWindow_hpp
#include <stdio.h>
#include <QLabel>

class FinalWindow : public QWidget {
 public:
  FinalWindow();
  ~FinalWindow();

 private:
  QLabel *FinalMessage;
};

#endif /* FinalWindow_hpp */
