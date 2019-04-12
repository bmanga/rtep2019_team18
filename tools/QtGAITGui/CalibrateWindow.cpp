#include "CalibrateWindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
CalibrateWindow::CalibrateWindow()
    : CalibrateButton(new QPushButton()), CalibrateText(new QLabel())
{
  CalibrateText->setText(R"(
                       <html>
                         <blockquote> <blockquote> <b>STEP 3:</b> Before your training begins, please click on <b>Calibrate</b> and stand still for about 5 seconds.  </blockquote> </blockquote>
                       </html>)");

  CalibrateText->setWordWrap(true);
  QFont font_message = CalibrateText->font();
  font_message.setPixelSize(28);
  CalibrateText->setFont(font_message);

  QFont font_next = CalibrateButton->font();
  font_next.setPixelSize(30);
  CalibrateButton->setFont(font_next);
  CalibrateButton->setText("Calibrate");

  QHBoxLayout *CalButtLay = new QHBoxLayout();
  CalButtLay->addSpacing(200);
  CalButtLay->addWidget(CalibrateButton);
  CalButtLay->addSpacing(200);

  QVBoxLayout *CalibrateLay = new QVBoxLayout();
  CalibrateLay->addWidget(CalibrateText);
  CalibrateLay->addSpacing(30);
  CalibrateLay->addLayout(CalButtLay);
  CalibrateLay->addSpacing(250);
  setLayout(CalibrateLay);

  QPalette pal = palette();
  QColor background(204, 225, 255);
  pal.setColor(QPalette::Background, background);
  setAutoFillBackground(true);
  setPalette(pal);
}
CalibrateWindow::~CalibrateWindow()
{
  delete CalibrateButton;
  delete CalibrateText;
}
