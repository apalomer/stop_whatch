#include "digitalclock.h"

DigitalClock::DigitalClock(uchar display, QWidget *parent) : AbstractClock(display, parent)
{
  // Preapare widget
  setWindowTitle(tr("Digital Clock"));

  // Set LCD
  lcd_ = new QLCDNumber;
  lcd_->setSegmentStyle(QLCDNumber::Filled);

  // Set up layout
  layout_ = new QVBoxLayout;
  this->setLayout(layout_);
  layout_->addWidget(lcd_);

  // Set timer
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(showTime()));
  timer_->start(1);

  // Draw
  showTime();
}

DigitalClock::DigitalClock(QWidget *parent) : DigitalClock(DISPLAY_H | DISPLAY_M | DISPLAY_S, parent)
{
}

DigitalClock::~DigitalClock()
{
  delete lcd_;
  delete timer_;
  delete layout_;
}

void DigitalClock::showTime()
{
  // Get time
  QTime time = QTime::currentTime();

  // Covnert to sting
  int step(250);
  QString text("");
  if (displayType_ & DISPLAY_H)
    text += time.toString("HH");
  if (displayType_ & DISPLAY_M)
  {
    if (displayType_ & DISPLAY_H)
    {
      if ((time.msec() / step) % 2 == 0)
        text += ":";
      else
        text += " ";
    }
    text += time.toString("mm");
  }
  if (displayType_ & DISPLAY_S)
  {
    if (displayType_ & DISPLAY_M || displayType_ & DISPLAY_H)
    {
      if ((time.msec() / step) % 2 == 0)
        text += ":";
      else
        text += " ";
    }
    text += time.toString("ss");
  }
  if (displayType_ & DISPLAY_MS)
  {
    if (displayType_ & DISPLAY_S || displayType_ & DISPLAY_M || displayType_ & DISPLAY_H)
      text += ".";
    text += time.toString("zzz");
  }

  // Set up display
  lcd_->setDigitCount(text.size());
  lcd_->display(text);
}
