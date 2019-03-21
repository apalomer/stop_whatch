#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QDebug>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include "abstractclock.h"

class DigitalClock : public AbstractClock
{
  Q_OBJECT
public:
  DigitalClock(QWidget* parent = nullptr);
  DigitalClock(uchar display, QWidget* parent = nullptr);
  ~DigitalClock();

private slots:
  void showTime();

private:
  QTimer* timer_;
  QLCDNumber* lcd_;
  QVBoxLayout* layout_;
};

#endif  // DIGITALCLOCK_H
