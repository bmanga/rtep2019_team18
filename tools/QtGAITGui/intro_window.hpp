//
//  intro_window.hpp
//  rtep_team18
//
//  Created by Luca Rosalia on 07/04/2019.
//

#ifndef intro_window_hpp
#define intro_window_hpp

#include <stdio.h>
#include <QLabel>
#include <QPushButton>
#include <QtWidgets/QMainWindow>

class IntroWindow : public QWidget {
 public:
  IntroWindow();
  ~IntroWindow();

  QPushButton *WSButton;
  QPushButton *CPButton;

 private:
  QLabel *Message;
};

#endif /* intro_window_hpp */
