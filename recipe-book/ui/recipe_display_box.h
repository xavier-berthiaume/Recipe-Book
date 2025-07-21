#ifndef RECIPE_DISPLAY_BOX_H
#define RECIPE_DISPLAY_BOX_H

#include "../models//qt_recipe_wrapper.h"
#include "generic_object_display_box.h"

#include <QLabel>

class RecipeDisplayBox : public GenericObjectDisplayBox<QtRecipeWrapper> {
  Q_OBJECT

  Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor)

  QLabel *m_name_label;
  QLabel *m_details_label;
  QLabel *m_stats_label;

  QColor m_normalColor = QColor("#f3e5f5");
  QColor m_hoverColor = QColor("#e1bee7");
  QPropertyAnimation *m_colorAnimation;

  bool m_pressed = false;

protected:
  void updateDisplay() override;

  void enterEvent(QEnterEvent *event) override;
  void leaveEvent(QEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

public:
  explicit RecipeDisplayBox(QWidget *parent = nullptr);

  QColor hoverColor() const;

  void setHoverColor(const QColor &color);
  void setWrapper(QtRecipeWrapper *wrapper) override;

signals:
  void clicked(QtRecipeWrapper *recipe);
  void wrapperChanged();
};

#endif
