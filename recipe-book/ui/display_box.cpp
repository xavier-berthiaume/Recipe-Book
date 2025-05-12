#include "display_box.h"

#include <QGraphicsEffect>
#include <QPainterPath>

DisplayBox::DisplayBox(QWidget *parent) : DisplayBox(0, 0, 0, parent) {}

DisplayBox::DisplayBox(quint32 width, quint32 height, quint16 radius,
                       QWidget *parent)
    : QWidget(parent), m_width(width), m_height(height), m_radius(radius) {

  setFixedSize(m_width, m_height);

  QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
  shadowEffect->setBlurRadius(15);              // Shadow softness
  shadowEffect->setColor(QColor(0, 0, 0, 160)); // Shadow color and transparency
  shadowEffect->setOffset(3, 3); // Shadow offset (right and down)
  this->setGraphicsEffect(shadowEffect);
}

quint32 DisplayBox::getWidth() const { return m_width; }

quint32 DisplayBox::getHeight() const { return m_height; }

quint16 DisplayBox::getRadius() const { return m_radius; }

void DisplayBox::setWidth(quint32 width) {
  m_width = width;
  setFixedWidth(m_width);
  update();
}

void DisplayBox::setHeight(quint32 height) {
  m_height = height;
  setFixedHeight(m_height);
  update();
}

void DisplayBox::setRadius(quint16 radius) {
  m_radius = radius;
  update();
}

QSize DisplayBox::sizeHint() const { return QSize(m_width, m_height); }

void DisplayBox::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QPainterPath path;
  path.addRoundedRect(rect(), m_radius, m_radius);

  painter.fillPath(path, QColor(Qt::white));

  painter.strokePath(path, QPen(Qt::black, 1));
}
