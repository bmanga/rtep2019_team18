#include "WelcomeWindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "MainWindow.hpp"

WelcomeWindow::WelcomeWindow()
    : ConnectLabel(new QLineEdit()),
      VocalInstructions(new QCheckBox()),
      NextButton(new QPushButton()),
      WelcomeText(new QLabel())

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
                       <blockquote>Click on the  <b>Speaker Icon</b>, if you require vocal assistance. <br> <br>
                       <b>STEP 1:</b> Insert the IP address of your device in the box below, or leave it blank to connect locally. Then click <b>Next</b>.</blockquote>
                  </p>
                   <br>
                   </html>)");

  WelcomeText->setWordWrap(true);
  QFont font_message = WelcomeText->font();
  font_message.setPixelSize(28);
  WelcomeText->setFont(font_message);

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

  QVBoxLayout *WelcomeLay = new QVBoxLayout();
  WelcomeLay->addWidget(WelcomeText);
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
}

void WelcomeWindow::onNextButtonPushed()
{
  static_cast<MainWindow *>(this->parent())
      ->connectToAddress(ConnectLabel->text().isEmpty() ? "localhost"
                                                        : ConnectLabel->text());
  emit windowDone(WindowKind::Welcome, 0);
}
WelcomeWindow::~WelcomeWindow() {}
