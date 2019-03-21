/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGridLayout>
#include <QtGui>

#include "analogclock.h"

AnalogClock::AnalogClock(QWidget *parent) : AnalogClock(DISPLAY_H | DISPLAY_M | DISPLAY_S, parent)
{
}

AnalogClock::AnalogClock(uchar display, QWidget *parent) : AbstractClock(display, parent)
{
  // Preapare widget
  setWindowTitle(tr("Analog Clock"));

  // Set timer
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
  timer_->start(1);

  // Repaint widget
  update();
}

AnalogClock::~AnalogClock()
{
  delete timer_;
}

void AnalogClock::paintEvent(QPaintEvent *)
{
  // Get time and side
  int side = qMin(width(), height());
  QTime time = QTime::currentTime();

  // Get painter ready
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 200.0, side / 200.0);

  // Define colors and shapes
  static const QPoint hourHand[3] = { QPoint(7, 8), QPoint(-7, 8), QPoint(0, -40) };
  QColor hourColor(127, 0, 127);
  static const QPoint minuteHand[3] = { QPoint(7, 8), QPoint(-7, 8), QPoint(0, -70) };
  QColor minuteColor(0, 127, 127, 191);
  static const QPoint secondHand[3] = { QPoint(2, 8), QPoint(-2, 8), QPoint(0, -70) };
  QColor secondColor(127, 127, 0);
  static const QPoint milliSecondHand[3] = { QPoint(2, 8), QPoint(-2, 8), QPoint(0, -90) };
  QColor milliSecondColor(0, 0, 0);

  // Paint hour handle
  if (getDisplayHours())
  {
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
  }

  // Paint cloc hours
  painter.setPen(Qt::NoPen);
  painter.setPen(hourColor);
  for (int i = 0; i < 12; ++i)
  {
    painter.drawLine(88, 0, 96, 0);
    painter.rotate(30.0);
  }

  // Paint minute handle
  if (getDisplayMinutes())
  {
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
  }

  // Paint minute clock
  painter.setPen(Qt::NoPen);
  painter.setPen(minuteColor);
  for (int j = 0; j < 60; ++j)
  {
    if ((j % 5) != 0)
      painter.drawLine(92, 0, 96, 0);
    painter.rotate(6.0);
  }

  // Paint second handle
  if (displayType_ & DISPLAY_S)
  {
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
  }

  // Paint millisecond handle
  if (displayType_ & DISPLAY_MS)
  {
    painter.setPen(Qt::NoPen);
    painter.setBrush(milliSecondColor);
    painter.save();
    painter.rotate(0.36 * time.msec());
    painter.drawConvexPolygon(milliSecondHand, 3);
    painter.restore();
  }
}
