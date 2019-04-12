#include "FinalWindow.hpp"
#include <QVBoxLayout>
FinalWindow::FinalWindow() : FinalMessage(new QLabel())
{
  FinalMessage->setText(R"(
                   <html>
                   <center><b>CONGRATULATIONS!</b>
                   <br>
                   <br>
                        Your training is now complete! </center>
                   </html>)");

  FinalMessage->setWordWrap(true);

  QFont font_message = FinalMessage->font();
  font_message.setPixelSize(28);
  FinalMessage->setFont(font_message);

  QVBoxLayout *FinMessLay = new QVBoxLayout();
  FinMessLay->addWidget(FinalMessage);

  setLayout(FinMessLay);
  QPalette pal = palette();
  QColor background(204, 225, 255);
  pal.setColor(QPalette::Background, background);
  setAutoFillBackground(true);
  setPalette(pal);
}
FinalWindow::~FinalWindow()
{
  delete FinalMessage;
}
