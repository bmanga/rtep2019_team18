#include "intro_window.hpp"
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "main_window.h"

IntroWindow::IntroWindow() : Message(new QLabel())
{
  GaitMode = new QPushButton("GAIT", this);
  TrainingMode = new QPushButton("TRAINING", this);
  QCheckBox *Vocal = new QCheckBox(this);
  Vocal->setText("Vocal Instructions");

  Message->setText(R"(
  <html>
        Please, select your preferred mode of choice:
        <br>
        <ul>
            <blockquote><b>GAIT</b> mode is to assist you during walking.</blockquote>
            <br>
            <blockquote><b>TRAINING</b> mode provides exercises to improve posture and motion. </blockquote>
        <br>
        </ul>
        First, tick the "Vocal Instructions" box, if you require vocal assistance.
        <br>
  </html>)");

  Message->setWordWrap(true);

  QFont font_message = Message->font();
  font_message.setPixelSize(28);
  Message->setFont(font_message);

  QFont font_vocal("Arial", 22);
  Vocal->setFont(font_vocal);

  QFont font("Arial", 40);
  font.setBold(true);
  GaitMode->setFont(font);
  TrainingMode->setFont(font);

  GaitMode->setStyleSheet("background-color: white");
  TrainingMode->setStyleSheet("background-color: white");
  QWidget *Intro = new QWidget();
  auto *IntroLay = new QVBoxLayout(Intro);
  IntroLay->addWidget(Message, 0, Qt::AlignCenter);
  IntroLay->addWidget(Vocal, 0, Qt::AlignCenter);
  IntroLay->addLayout([&] {
    QHBoxLayout *l = new QHBoxLayout();
    l->addWidget(GaitMode);
    l->addSpacing(50);
    l->addWidget(TrainingMode);
    return l;
  }());
  Intro->setLayout(IntroLay);
  setCentralWidget(Intro);
  Intro->show();
  Intro->resize(700, 700);
}

IntroWindow::~IntroWindow()
{
  delete Message;
}
