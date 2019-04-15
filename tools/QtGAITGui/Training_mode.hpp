#ifndef Training_mode_hpp
#define Training_mode_hpp

#include <stdio.h>
#include <CircleWidget.hpp>
#include <QGridLayout>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QtWidgets/QMainWindow>
#include <chrono>
#include "Level_weight_shifting.hpp"
#include "WindowBase.hpp"
#include "progressbar.hpp"
#include "telemetry/client.h"

class ProgressBar;
class CircleWidget;

template <class WidgetT>
class TrainingMode : public WindowBase {
 public:
  TrainingMode(QString instructions, QMainWindow *parent)
      : widget_r(new WidgetT()),
        widget_l(new WidgetT()),
        level_label(new QLabel()),
        instruction_label(new QLabel(instructions)),
        level_manager(this, widget_l, widget_r, level_label)

  {
    QPalette pal = palette();
    QColor background(204, 225, 255);
    pal.setColor(QPalette::Background, background);
    setAutoFillBackground(true);
    setPalette(pal);

    double calibrationMax = static_cast<MainWindow *>(parent)->calibrationMax;
    widget_l->setMaxValue(calibrationMax);
    widget_r->setMaxValue(calibrationMax);

    instruction_label->setWordWrap(true);
    QFont font_message = instruction_label->font();
    font_message.setPixelSize(28);
    instruction_label->setFont(font_message);
    auto *left_label = new QLabel();
    auto *right_label = new QLabel();
    left_label->setText("Left");
    QFont font_label_level("Arial", 30);
    QFont font_label_foot("Arial", 36);
    left_label->setFont(font_label_foot);
    right_label->setText("Right");
    right_label->setFont(font_label_foot);
    level_label->setText("<b>Level 1</b>");

    level_label->setFont(font_label_level);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(left_label, 1, 0, Qt::AlignCenter);
    grid->addWidget(widget_l, 0, 0, Qt::AlignCenter);
    grid->addWidget(right_label, 1, 1, Qt::AlignCenter);
    grid->addWidget(widget_r, 0, 1, Qt::AlignCenter);
    grid->setSpacing(50);

    QVBoxLayout *ExerciseLay = new QVBoxLayout();
    ExerciseLay->addWidget(instruction_label);
    ExerciseLay->addWidget(level_label, 1, Qt::AlignCenter);
    ExerciseLay->addLayout(grid);
    setLayout(ExerciseLay);

    connect(static_cast<MainWindow *>(parent), &MainWindow::newFSRDataL,
            widget_l, &WidgetT::onNewFSRData);
    connect(static_cast<MainWindow *>(parent), &MainWindow::newFSRDataR,
            widget_r, &WidgetT::onNewFSRData);

    level_manager.loadJsonFile("levels.json");
    level_manager.start();
  }

  void emitWindowDone() { emit windowDone(WindowKind::Training, 0); }

 private:
  WidgetT *widget_r;
  WidgetT *widget_l;

  QLabel *left_label;
  QLabel *right_label;

  QLabel *level_label;
  QLabel *instruction_label;

  LevelWS<WidgetT> level_manager;
};

#endif /* Training_mode_hpp */
