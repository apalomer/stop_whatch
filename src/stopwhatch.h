#ifndef STOPWHATCH_H
#define STOPWHATCH_H

#include <QWidget>

namespace Ui
{
class StopWhatch;
}

class StopWhatch : public QWidget
{
  Q_OBJECT

public:
  explicit StopWhatch(QWidget* parent = nullptr);
  ~StopWhatch();
public slots:

  void startChrono();

  void stopChrono();

protected slots:

  virtual void keyPressEvent(QKeyEvent* event);

private:
  Ui::StopWhatch* ui;
};

#endif  // STOPWHATCH_H
