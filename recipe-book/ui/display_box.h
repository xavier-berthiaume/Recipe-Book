#ifndef DISPLAY_BOX_H
#define DISPLAY_BOX_H

#include <QWidget>
#include <qtypes.h>

class DisplayBox : public QWidget {
  Q_OBJECT

  quint32 width, height;
  quint16 radius;

public:
  explicit DisplayBox(QWidget *parent = nullptr);
  explicit DisplayBox(quint32 width, quint32 height, quint16 radius,
                      QWidget *parent = nullptr);

  quint32 getWidth() const;
  quint32 getHeight() const;
  quint16 getRadius() const;

  void setWidth(quint32 width);
  void setHeight(quint32 height);
  void setRadius(quint16 radius);
};

#endif
