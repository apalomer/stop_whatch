#include "abstractclock.h"
#include <math.h>

AbstractClock::AbstractClock(QWidget *parent) : AbstractClock(DISPLAY_H | DISPLAY_M | DISPLAY_S, parent)
{
}

AbstractClock::AbstractClock(uchar display, QWidget *parent) : QLCDNumber(parent), displayType_(display)
{
}

void AbstractClock::setDisplay(uchar display)
{
  displayType_ = display;
  emit displayTypeUpdated();
  emit displayTypeUpdated(display);
  emit displayTypeUpdated(this);
}

uchar AbstractClock::getDisplayType()
{
  return displayType_;
}

bool AbstractClock::getDisplayHours()
{
  return displayType_ & DISPLAY_H;
}

bool AbstractClock::getDisplayMinutes()
{
  return displayType_ & DISPLAY_M;
}

bool AbstractClock::getDisplaySeconds()
{
  return displayType_ & DISPLAY_S;
}

bool AbstractClock::getDisplayMilliseconds()
{
  return displayType_ & DISPLAY_MS;
}

void AbstractClock::setDisplayHours(bool display)
{
  if (display)
    addDisplay(DISPLAY_H);
  else
    removeDisplay(DISPLAY_H);
}

void AbstractClock::setDisplayMinutes(bool display)
{
  if (display)
    addDisplay(DISPLAY_M);
  else
    removeDisplay(DISPLAY_M);
}

void AbstractClock::setDisplaySeconds(bool display)
{
  if (display)
    addDisplay(DISPLAY_S);
  else
    removeDisplay(DISPLAY_S);
}

void AbstractClock::setDisplayMilliseconds(bool display)
{
  if (display)
    addDisplay(DISPLAY_MS);
  else
    removeDisplay(DISPLAY_MS);
}

void AbstractClock::addDisplay(uchar display)
{
  displayType_ |= display;
  emit displayTypeUpdated();
  emit displayTypeUpdated(displayType_);
  emit displayTypeUpdated(this);
}

void AbstractClock::removeDisplay(uchar display)
{
  displayType_ &= ~(1u << (int)log2(display));
  emit displayTypeUpdated();
  emit displayTypeUpdated(displayType_);
  emit displayTypeUpdated(this);
}
