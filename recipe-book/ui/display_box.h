#ifndef DISPLAY_BOX_H
#define DISPLAY_BOX_H

#include <QEnterEvent>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPropertyAnimation>
#include <QWidget>
#include <QtTypes>

class DisplayBox : public QWidget {
  Q_OBJECT

  // Visual properties
  Q_PROPERTY(float scaleFactor READ scaleFactor WRITE setScaleFactor)
  Q_PROPERTY(
      QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
  Q_PROPERTY(
      int animationDuration READ animationDuration WRITE setAnimationDuration)
  Q_PROPERTY(QColor shadowColor READ shadowColor WRITE setShadowColor)
  Q_PROPERTY(
      qreal shadowBlurRadius READ shadowBlurRadius WRITE setShadowBlurRadius)
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

  // Dimensions
  quint32 m_width;
  quint32 m_height;
  quint16 m_radius;

  // Visual state
  float m_scaleFactor = 1.0f;
  QColor m_backgroundColor;
  QColor m_borderColor = Qt::transparent;
  QColor m_textColor;

  // Effects
  QGraphicsDropShadowEffect *m_shadowEffect;
  QPropertyAnimation *m_hoverAnimation;
  int m_animationDuration = 200;

public:
  explicit DisplayBox(QWidget *parent = nullptr);
  explicit DisplayBox(quint32 width, quint32 height, quint16 radius,
                      QWidget *parent = nullptr);
  ~DisplayBox() override;

  // Dimension accessors
  quint32 width() const;
  quint32 height() const;
  quint16 radius() const;

  // Visual property accessors
  float scaleFactor() const;
  QColor backgroundColor() const;
  QColor borderColor() const;
  QColor textColor() const;
  int animationDuration() const;
  QColor shadowColor() const;
  qreal shadowBlurRadius() const;

  // Setters
  void setWidth(quint32 width);
  void setHeight(quint32 height);
  void setRadius(quint16 radius);
  void setScaleFactor(float factor);
  void setBackgroundColor(const QColor &color);
  void setBorderColor(const QColor &color);
  void setTextColor(const QColor &color);
  void setAnimationDuration(int duration);
  void setShadowColor(const QColor &color);
  void setShadowBlurRadius(qreal radius);

protected:
  // Event handlers
  void enterEvent(QEnterEvent *event) override;
  void leaveEvent(QEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

  // Size management
  QSize sizeHint() const override;
};

#endif
