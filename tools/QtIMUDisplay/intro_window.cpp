//
//  intro_window.cpp
//  rtep_team18
//
//  Created by Luca Rosalia on 07/04/2019.
//

#include "intro_window.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

IntroWindow::IntroWindow() : Message(new QLabel())
{
  GaitMode = new QPushButton("GAIT", this);
  TrainingMode = new QPushButton("TRAINING", this);

  Message->setText(
      "Please, select your preferred mode of choice:\n GAIT mode is to assist "
      "you during your walking.\nTRAINING mode provides exercises aimed to "
      "improve your posture and motion.");
  Message->setWordWrap(true);

  QFont font_message = Message->font();
  font_message.setPixelSize(28);
  Message->setFont(font_message);

  QFont font = GaitMode->font();
  font.setBold(true);     // set style bold if is true
  font.setPixelSize(48);  // Sets the font size to pixelSize pixels.
  GaitMode->setFont(font);
  // change color
  QString Buttonstyle = "QPushButton {background-color: #0000FF, color: red;}";

  GaitMode->setStyleSheet(Buttonstyle);
  GaitMode->resize({200}, {100});
  QWidget *Intro = new QWidget();
  QGridLayout *IntroLay = new QGridLayout(Intro);
  IntroLay->addWidget(Message, 0, 0, 1, 2, Qt::AlignCenter);
  IntroLay->addWidget(GaitMode, 1, 0, Qt::AlignCenter);
  IntroLay->addWidget(TrainingMode, 1, 1, Qt::AlignCenter);
  Intro->setLayout(IntroLay);
  setCentralWidget(Intro);
  Intro->show();
  Intro->resize(700, 700);
  // Add speaker option
}

IntroWindow::~IntroWindow()
{
  delete Message;
}
