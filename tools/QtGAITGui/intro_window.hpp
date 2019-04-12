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
#include "WindowBase.hpp"

<<<<<<< HEAD:tools/QtGAITGui/intro_window.hpp
class IntroWindow : public WindowBase {
=======
class IntroWindow : public QWidget {
>>>>>>> Edited GUI, now works with realtime data from sensors.:tools/QtGAITGui/intro_window.hpp
 public:
  IntroWindow();
  ~IntroWindow();

  QPushButton *WSButton;
  QPushButton *CPButton;
<<<<<<< HEAD:tools/QtGAITGui/intro_window.hpp

 private slots:
  void onWSButtonPushed();
  void onCPButtonPushed();
=======
>>>>>>> Edited GUI, now works with realtime data from sensors.:tools/QtGAITGui/intro_window.hpp

 private:
  QLabel *Message;
};

#endif /* intro_window_hpp */
