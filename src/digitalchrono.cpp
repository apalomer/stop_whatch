#include "digitalchrono.h"

#include <QAction>
#include <QMenu>

DigitalChrono::DigitalChrono(uchar display, QWidget *parent) : AbstractClock(display, parent)
{
  // Preapare widget
  setWindowTitle(tr("Digital Clock"));

  // Set context menu policy
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &DigitalChrono::customContextMenuRequested, this, &DigitalChrono::showContextMenu);

  // Set LCD
  setSegmentStyle(QLCDNumber::Filled);

  // Set timer
  timer_ = new QTimer(this);
  timer_->start(1);

  // Actions
  action_start_chrono_ = new QAction("Start", this);
  connect(action_start_chrono_, &QAction::triggered, this, &DigitalChrono::startChrono);
  action_stop_chrono_ = new QAction("Stop", this);
  connect(action_stop_chrono_, &QAction::triggered, this, &DigitalChrono::stopChrono);
  action_disply_ms_ = new QAction("Display ms", this);
  action_disply_ms_->setCheckable(true);
  action_disply_ms_->setChecked(false);
  connect(action_disply_ms_, &QAction::toggled, this, &DigitalChrono::setDisplayMilliseconds);
  connect(action_disply_ms_, &QAction::toggled, this, &DigitalChrono::showTime);

  // Draw
  showTime();
}

DigitalChrono::DigitalChrono(QWidget *parent) : DigitalChrono(DISPLAY_H | DISPLAY_M | DISPLAY_S, parent)
{
}

DigitalChrono::~DigitalChrono()
{
}

void DigitalChrono::showTime()
{
  // Get time
  double t = chorno_timer_.elapsed();  // ms
  int h = t / 1000 * 1 / 60 * 1 / 60;
  int minutes = (int(t) / 1000 * 1 / 60) % 60;
  int sec = (int(t) / 1000) % 60;
  int msec = t - sec * 1000 - minutes * 1000 * 60 - h * 1000 * 60 * 60;
  if (t < 0)
  {
    h = 0;
    minutes = 0;
    sec = 0;
    msec = 0;
  }

  // Covnert to sting
  int step(500);
  QString text("");
  if (displayType_ & DISPLAY_H)
    text += QString::number(h).rightJustified(2, '0');
  if (displayType_ & DISPLAY_M)
  {
    if (displayType_ & DISPLAY_H)
    {
      if ((msec / step) % 2 == 0)
        text += ":";
      else
        text += " ";
    }
    text += QString::number(minutes).rightJustified(2, '0');
  }
  if (displayType_ & DISPLAY_S)
  {
    if (displayType_ & DISPLAY_M || displayType_ & DISPLAY_H)
    {
      if ((msec / step) % 2 == 0)
        text += ":";
      else
        text += " ";
    }
    text += QString::number(sec).rightJustified(2, '0');
  }
  if (displayType_ & DISPLAY_MS)
  {
    if (displayType_ & DISPLAY_S || displayType_ & DISPLAY_M || displayType_ & DISPLAY_H)
      text += ".";
    text += QString::number(msec).rightJustified(3, '0');
  }

  // Set up display
  setDigitCount(text.size());
  display(text);
}

void DigitalChrono::startChrono()
{
  chorno_timer_.start();
  connect(timer_, SIGNAL(timeout()), this, SLOT(showTime()));
}

void DigitalChrono::stopChrono()
{
  disconnect(timer_, SIGNAL(timeout()), this, SLOT(showTime()));
}

void DigitalChrono::showContextMenu(const QPoint &pos)
{
  QMenu menu("Context menu", this);
  menu.addAction(action_start_chrono_);
  menu.addAction(action_stop_chrono_);
  menu.addAction(action_disply_ms_);
  menu.exec(mapToGlobal(pos));
}
