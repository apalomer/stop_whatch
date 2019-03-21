#ifndef LOGOSDISPLAY_H
#define LOGOSDISPLAY_H

#include <QWidget>

class LogosDisplay : public QWidget
{
  Q_OBJECT
public:
  explicit LogosDisplay(QWidget* parent = nullptr);

signals:

public slots:

  void addLogo();

  void addLogo(QString logo_path);

  void addLogo(QImage logo);

  void addLogo(QPixmap logo);

protected slots:

  void showContextMenu(const QPoint& pos);

protected:
  void paintEvent(QPaintEvent* event);

private:
  QAction* action_add_logo_;

  QList<QPixmap> pixmaps_;

  double offset_ = 0;

  double direction_ = -1;
};

#endif  // LOGOSDISPLAY_H
