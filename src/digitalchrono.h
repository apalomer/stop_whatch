#ifndef DIGITALCHRONO_H
#define DIGITALCHRONO_H

#include <QDebug>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include "abstractclock.h"

class DigitalChrono : public AbstractClock
{
  Q_OBJECT
public:
  DigitalChrono(QWidget* parent = nullptr);
  DigitalChrono(uchar display, QWidget* parent = nullptr);
  ~DigitalChrono();

private slots:
  void showTime();

public slots:
  void startChrono();
  void stopChrono();
protected slots:

  void showContextMenu(const QPoint& pos);

private:
  QTimer* timer_;

  QElapsedTimer chorno_timer_;

  QAction* action_start_chrono_;
  QAction* action_stop_chrono_;
  QAction* action_disply_ms_;
};

#endif  // DIGITALCHRONO_H
