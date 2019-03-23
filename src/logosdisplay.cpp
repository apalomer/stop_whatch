#include "logosdisplay.h"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QPainter>
#include <QTimer>

LogosDisplay::LogosDisplay(QWidget *parent) : QWidget(parent)
{
  action_add_logo_ = new QAction("Add logos", this);
  connect(action_add_logo_, &QAction::triggered, this, QOverload<>::of(&LogosDisplay::addLogo));

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &LogosDisplay::customContextMenuRequested, this, &LogosDisplay::showContextMenu);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, QOverload<>::of(&LogosDisplay::update));
  timer->start(10);
}

void LogosDisplay::addLogo()
{
  QStringList file_names = QFileDialog::getOpenFileNames(this, "Add logos", "", "Images (*.png *.xpm *.jpg)");
  for (auto f : file_names)
    addLogo(f);
}

void LogosDisplay::addLogo(QString logo_path)
{
  addLogo(QImage(logo_path));
}

void LogosDisplay::addLogo(QImage logo)
{
  addLogo(QPixmap::fromImage(logo));
}

void LogosDisplay::addLogo(QPixmap logo)
{
  pixmaps_.push_back(logo);
}

void LogosDisplay::showContextMenu(const QPoint &pos)
{
  QMenu menu("Context menu", this);
  menu.addAction(action_add_logo_);
  menu.exec(mapToGlobal(pos));
}

void LogosDisplay::paintEvent(QPaintEvent *)
{
  if (pixmaps_.size() == 0)
    return;

  QPainter painter(this);
  if (pixmaps_.size() == 1)
  {
    double ratio = float(pixmaps_[0].height()) / float(height());
    QRectF target(QPointF(width() / 2 - pixmaps_[0].width() / 2 * 1 / ratio, 0),
                  QSizeF(pixmaps_[0].width() / ratio, pixmaps_[0].height() / ratio));
    painter.drawPixmap(target, pixmaps_[0], pixmaps_[0].rect());
    return;
  }
  //  double last(-offset_);
  double last(offset_);
  for (int i = 0; i < pixmaps_.size(); i++)
  {
    double ratio = float(pixmaps_[i].height()) / float(height());
    QRectF target(QPointF(last, 0), QSizeF(pixmaps_[i].width() / ratio, pixmaps_[i].height() / ratio));
    last = target.right();
    painter.drawPixmap(target, pixmaps_[i], pixmaps_[i].rect());
  }
  offset_ += direction_;
  if (last + offset_ < width() && direction_ < 0)
    direction_ *= -1;
  else if (offset_ >= 0)
    direction_ *= -1;
}
