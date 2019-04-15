#include "intro_window.hpp"
#include <QCheckBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPushButton>
#include <QSplineSeries>
#include <QtCharts/QChartView>
#include <QtTextToSpeech/QTextToSpeech>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "MainWindow.hpp"
#include "WindowBase.hpp"

IntroWindow::IntroWindow(QMainWindow *parent)
    : WindowBase(parent), Message(new QLabel()), m_speech(new QTextToSpeech())
{
  WSButton = new QPushButton("Weight Shifting", this);
  CPButton = new QPushButton("Calf Pushes", this);

  Message->setText(R"(
  <html>
                   <b>STEP 2:</b> Please, select your exercise of choice:
        <br>
        <ul>
            <blockquote><b>Weight Shifting</b> requires shifting of your body weight from one foot to the other.</blockquote>
            <br>
            <blockquote><b>Calf Pushes</b> requires shifting of your body weight from heel to toes. </blockquote>
        <br>
        </ul>
  </html>)");

  Message->setWordWrap(true);

  QFont font_message = Message->font();
  font_message.setPixelSize(28);
  Message->setFont(font_message);

  QFont font("Arial", 30);
  WSButton->setFont(font);
  CPButton->setFont(font);

  // WSButton->setStyleSheet("background-color: lightgrey");
  // CPButton->setStyleSheet("background-color: lightgrey");
  auto *IntroLay = new QVBoxLayout();
  IntroLay->addWidget(Message, 0, Qt::AlignCenter);
  IntroLay->addLayout([&] {
    QHBoxLayout *l = new QHBoxLayout();
    l->addSpacing(200);
    l->addWidget(WSButton);
    l->addSpacing(200);
    return l;
  }());
  IntroLay->addLayout([&] {
    QHBoxLayout *l = new QHBoxLayout();
    l->addSpacing(200);
    l->addWidget(CPButton);
    l->addSpacing(200);
    return l;
  }());
  IntroLay->addSpacing(60);
  setLayout(IntroLay);
  QPalette pal = palette();
  QColor background(204, 225, 255);
  pal.setColor(QPalette::Background, background);
  setAutoFillBackground(true);
  setPalette(pal);

  connect(WSButton, &QPushButton::clicked, this,
          &IntroWindow::onWSButtonPushed);
  connect(CPButton, &QPushButton::clicked, this,
          &IntroWindow::onCPButtonPushed);
  checkVoiceEnabled();
}

IntroWindow::~IntroWindow()
{
  delete Message;
}

void IntroWindow::onWSButtonPushed()
{
  emit windowDone(WindowKind::Intro, 0);
}
void IntroWindow::onCPButtonPushed()
{
  emit windowDone(WindowKind::Intro, 1);
}

void IntroWindow::checkVoiceEnabled()
{
  if (static_cast<MainWindow *>(parent())->getVoiceEnabled() == true) {
    m_speech->setPitch(-0.3);
    m_speech->setRate(-0.3);
    m_speech->setVolume(.8);
    m_speech->say(
        "Please select your exercise of choice. Weight Shifting requires "
        "shifting of your body weight from one foot, to the other. ");
    m_speech->say(
        "Calf Pushes requires shifting of your body weight from heel to toes.");
  }
}