#ifndef DISPLAY_BOX_H
#define DISPLAY_BOX_H

#include <QPainter>
#include <QWidget>
#include <QtTypes>

class DisplayBox : public QWidget {
  Q_OBJECT

  quint32 m_width, m_height;
  quint16 m_radius;

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

protected:
  void paintEvent(QPaintEvent *event) override;
  QSize sizeHint() const override;
};

#endif
