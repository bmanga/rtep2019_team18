#ifndef FinalWindow_hpp
#define FinalWindow_hpp
#include <stdio.h>
#include <QLabel>
#include "WindowBase.hpp"

class FinalWindow : public WindowBase {
 public:
  FinalWindow();
  ~FinalWindow();

 private:
  QLabel *FinalMessage;
};

#endif /* FinalWindow_hpp */
