#include "display_box.h"
#include <QGraphicsEffect>
#include <QPainterPath>
#include <qcolor.h>
#include <qguiapplication_platform.h>

DisplayBox::DisplayBox(QWidget *parent) : DisplayBox(0, 0, 0, parent) {}

DisplayBox::DisplayBox(quint32 width, quint32 height, quint16 radius,
                       QWidget *parent)
    : QWidget(parent), m_width(width), m_height(height), m_radius(radius),
      m_shadowEffect(new QGraphicsDropShadowEffect(this)),
      m_hoverAnimation(new QPropertyAnimation(this, "scaleFactor")),
      m_textColor(Qt::black) {
  setFixedSize(m_width, m_height);

  // Shadow setup
  m_shadowEffect->setBlurRadius(10);
  m_shadowEffect->setOffset(0, 0);
  m_shadowEffect->setColor(QColor(0, 0, 0, 60));
  setGraphicsEffect(m_shadowEffect);

  // Animation setup
  m_hoverAnimation->setDuration(m_animationDuration);
  m_hoverAnimation->setEasingCurve(QEasingCurve::OutQuad);

  setAttribute(Qt::WA_Hover);
}

DisplayBox::~DisplayBox() {
  // Clean up animations and effects
  m_hoverAnimation->deleteLater();
  m_shadowEffect->deleteLater();
}

// Dimension accessors
quint32 DisplayBox::width() const { return m_width; }

quint32 DisplayBox::height() const { return m_height; }

quint16 DisplayBox::radius() const { return m_radius; }

// Visual property accessors
float DisplayBox::scaleFactor() const { return m_scaleFactor; }

QColor DisplayBox::backgroundColor() const { return m_backgroundColor; }

QColor DisplayBox::borderColor() const { return m_borderColor; }

QColor DisplayBox::textColor() const { return m_textColor; }

int DisplayBox::animationDuration() const { return m_animationDuration; }

QColor DisplayBox::shadowColor() const {
  return m_shadowEffect ? m_shadowEffect->color() : QColor();
}

qreal DisplayBox::shadowBlurRadius() const {
  return m_shadowEffect ? m_shadowEffect->blurRadius() : 0.0;
}

// Setters
void DisplayBox::setWidth(quint32 width) {
  if (m_width != width) {
    m_width = width;
    setFixedWidth(m_width);
    update();
  }
}

void DisplayBox::setHeight(quint32 height) {
  if (m_height != height) {
    m_height = height;
    setFixedHeight(m_height);
    update();
  }
}

void DisplayBox::setRadius(quint16 radius) {
  if (m_radius != radius) {
    m_radius = radius;
    update();
  }
}

void DisplayBox::setScaleFactor(float factor) {
  if (!qFuzzyCompare(m_scaleFactor, factor)) {
    m_scaleFactor = factor;
    update();
  }
}

void DisplayBox::setBackgroundColor(const QColor &color) {
  if (m_backgroundColor != color) {
    m_backgroundColor = color;
    update();
  }
}

void DisplayBox::setBorderColor(const QColor &color) {
  if (m_borderColor != color) {
    m_borderColor = color;
    update();
  }
}

void DisplayBox::setTextColor(const QColor &color) {
  if (m_textColor != color) {
    m_textColor = color;
    update();
  }
}

void DisplayBox::setAnimationDuration(int duration) {
  if (m_animationDuration != duration) {
    m_animationDuration = duration;
    m_hoverAnimation->setDuration(duration);
  }
}

void DisplayBox::setShadowColor(const QColor &color) {
  if (m_shadowEffect && m_shadowEffect->color() != color) {
    m_shadowEffect->setColor(color);
    update();
  }
}

void DisplayBox::setShadowBlurRadius(qreal radius) {
  if (m_shadowEffect && !qFuzzyCompare(m_shadowEffect->blurRadius(), radius)) {
    m_shadowEffect->setBlurRadius(radius);
    update();
  }
}

QSize DisplayBox::sizeHint() const { return QSize(m_width, m_height); }

void DisplayBox::enterEvent(QEnterEvent *event) {
  QWidget::enterEvent(event);
  m_hoverAnimation->stop();
  m_hoverAnimation->setStartValue(scaleFactor());
  m_hoverAnimation->setEndValue(1.05f); // 5% scale up
  m_hoverAnimation->start();
}

void DisplayBox::leaveEvent(QEvent *event) {
  QWidget::leaveEvent(event);
  m_hoverAnimation->stop();
  m_hoverAnimation->setStartValue(scaleFactor());
  m_hoverAnimation->setEndValue(1.0f); // Return to normal size
  m_hoverAnimation->start();
}

void DisplayBox::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QTransform transform;
  transform.translate(width() / 2, height() / 2);
  transform.scale(m_scaleFactor, m_scaleFactor);
  transform.translate(-width() / 2, -height() / 2);
  painter.setTransform(transform);

  QPainterPath path;
  path.addRoundedRect(rect(), m_radius, m_radius);

  painter.fillPath(path, QColor(Qt::white));

  // painter.strokePath(path, QPen(Qt::black, 1));
}
