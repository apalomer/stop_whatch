#include "stopwhatch.h"
#include "ui_stopwhatch.h"

#include <QKeyEvent>

StopWhatch::StopWhatch(QWidget* parent) : QWidget(parent), ui(new Ui::StopWhatch)
{
  ui->setupUi(this);
}

StopWhatch::~StopWhatch()
{
  delete ui;
}

void StopWhatch::startChrono()
{
  ui->chrono->startChrono();
}

void StopWhatch::stopChrono()
{
  ui->chrono->stopChrono();
}

void StopWhatch::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_F11)
  {
    if (isFullScreen())
      setWindowState(Qt::WindowNoState);
    else
      setWindowState(Qt::WindowFullScreen);
  }
}
