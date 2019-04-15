#include "WelcomeWindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtTextToSpeech/QTextToSpeech>
#include "MainWindow.hpp"

WelcomeWindow::WelcomeWindow()
    : ConnectLabel(new QLineEdit()),
      VocalInstructions(new QCheckBox()),
      NextButton(new QPushButton()),
      WelcomeText(new QLabel()),
      ConnectText(new QLabel()),
      m_speech(new QTextToSpeech())

{
  WelcomeText->setText(R"(
                   <html>
                  <center><b>Welcome to Training mode!</b> <\center>
                  <br>
                  <br>
                  During this training session, you can select different exercises to improve your mobility!
                  <br>
                  <br>
                  Please, refer to your doctor for further advice.
                  <br>
                  <hr>
                  <p align = "left">
                       <blockquote>Click on the  <b>Check Box</b>, if you require vocal assistance. <br> <br>
                       <b>STEP 1:</b> Insert the IP address of your device in the box below, or leave it blank to connect locally. Then click <b>Next</b>.</blockquote>
                  </p>
                   <br>
                   </html>)");

  WelcomeText->setWordWrap(true);
  QFont font_message = WelcomeText->font();
  font_message.setPixelSize(28);
  WelcomeText->setFont(font_message);

  ConnectText->setText(R"(
                          <html>
                          <br>
                          <p align = "left">
                            <blockquote><b>STEP 1:</b> Insert the IP address of your device in the box below, or leave it blank to connect locally. Then click <b>Next</b>.</blockquote> <br> <br>
                          </p>
                          <./html>)");
  ConnectText->setWordWrap(true);
  ConnectText->setFont(font_message);

  QFont font_next = NextButton->font();
  font_next.setPixelSize(30);
  NextButton->setFont(font_next);
  NextButton->setText("Next");

  QHBoxLayout *ConnectLay = new QHBoxLayout();
  ConnectLay->addSpacing(200);
  ConnectLay->addWidget(ConnectLabel);
  ConnectLay->addSpacing(200);

  QHBoxLayout *NextLay = new QHBoxLayout();
  NextLay->addSpacing(200);
  NextLay->addWidget(NextButton);
  NextLay->addSpacing(200);

  VocalInstructions->setText("Enable Audio: ");
  VocalInstructions->setLayoutDirection(Qt::RightToLeft);
  VocalInstructions->setFont(font_next);
  VocalInstructions->setStyleSheet(
      "QCheckBox::indicator{width:50px; height:50px;}");

  QHBoxLayout *VocalLay = new QHBoxLayout();
  VocalLay->addSpacing(200);
  VocalLay->addWidget(VocalInstructions);
  VocalLay->addSpacing(200);

  QVBoxLayout *WelcomeLay = new QVBoxLayout();
  WelcomeLay->addWidget(WelcomeText);
  WelcomeLay->addLayout(VocalLay);
  WelcomeLay->addWidget(ConnectText);
  WelcomeLay->addLayout(ConnectLay);
  WelcomeLay->addLayout(NextLay);
  WelcomeLay->addSpacing(5);
  setLayout(WelcomeLay);
  QPalette pal = palette();
  QColor background(204, 225, 255);
  pal.setColor(QPalette::Background, background);
  setAutoFillBackground(true);
  setPalette(pal);

  connect(NextButton, &QPushButton::clicked, this,
          &WelcomeWindow::onNextButtonPushed);
  connect(VocalInstructions, &QCheckBox::clicked, this,
          &WelcomeWindow::checkBoxClicked);
}

void WelcomeWindow::onNextButtonPushed()
{
  static_cast<MainWindow *>(this->parent())
      ->connectToAddress(ConnectLabel->text().isEmpty() ? "localhost"
                                                        : ConnectLabel->text());
  emit windowDone(WindowKind::Welcome, 0);
}

WelcomeWindow::~WelcomeWindow() {}

void WelcomeWindow::checkBoxClicked()
{
  static_cast<MainWindow *>(parent())->toggleVoice(true);

  if (VocalInstructions->checkState() == 2) {
    m_speech->setPitch(-0.3);
    m_speech->setRate(-0.3);
    m_speech->setVolume(.8);
    m_speech->say(
        "Vocal instructions. Please insert IP Address of your device below, or "
        "leave blank to connect locally.");
  }
}