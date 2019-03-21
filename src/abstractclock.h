#ifndef ABSTRACTCLOCK_H
#define ABSTRACTCLOCK_H

#include <QElapsedTimer>
#include <QLCDNumber>

class AbstractClock : public QLCDNumber
{
  Q_OBJECT
  Q_PROPERTY(bool Hours READ getDisplayHours WRITE setDisplayHours)
  Q_PROPERTY(bool Minutes READ getDisplayMinutes WRITE setDisplayMinutes)
  Q_PROPERTY(bool Seconds READ getDisplaySeconds WRITE setDisplaySeconds)
  Q_PROPERTY(bool Milliseconds READ getDisplayMilliseconds WRITE setDisplayMilliseconds)
public:
  enum DISPLAY
  {
    DISPLAY_MS = 0X01,
    DISPLAY_S = 0X02,
    DISPLAY_M = 0X04,
    DISPLAY_H = 0X08
  };
  explicit AbstractClock(QWidget *parent = nullptr);
  explicit AbstractClock(uchar display, QWidget *parent = nullptr);

  uchar getDisplayType();
  bool getDisplayHours();
  bool getDisplayMinutes();
  bool getDisplaySeconds();
  bool getDisplayMilliseconds();

public slots:
  void addDisplay(uchar display);
  void removeDisplay(uchar display);
  void setDisplay(uchar display);
  void setDisplayHours(bool display);
  void setDisplayMinutes(bool display);
  void setDisplaySeconds(bool display);
  void setDisplayMilliseconds(bool display);

signals:
  void displayTypeUpdated(AbstractClock *AbstractClock);
  void displayTypeUpdated(uchar display);
  void displayTypeUpdated();

protected:
  uchar displayType_;
};

#endif  // ABSTRACTCLOCK_H
