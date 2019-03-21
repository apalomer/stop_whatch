#include <QApplication>
#include <QLayout>
#include <QPushButton>
#include "stopwhatch.h"

int main(int argc, char** argv)
{
  // Application
  QApplication app(argc, argv);

  // Clock
  StopWhatch* sw = new StopWhatch;
  sw->show();

  // Exit
  return app.exec();
}
