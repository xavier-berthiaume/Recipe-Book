#ifndef INGREDIENT_DISPLAY_BOX_H
#define INGREDIENT_DISPLAY_BOX_H

#include "../models/qt_ingredient_wrapper.h"
#include "generic_object_display_box.h"

#include <QLabel>

class IngredientDisplayBox
    : public GenericObjectDisplayBox<QtIngredientWrapper> {
  Q_OBJECT

  QLabel *m_name_label;
  QLabel *m_description_label;

  bool m_pressed = false;

protected:
  void updateDisplay() override;

  // void enterEvent(QEnterEvent *event) override;
  // void leaveEvent(QEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

public:
  explicit IngredientDisplayBox(QWidget *parent = nullptr);
  explicit IngredientDisplayBox(QtIngredientWrapper *wrapper,
                                QWidget *parent = nullptr);

  void setWrapper(QtIngredientWrapper *wrapper) override;

signals:
  void clicked(QtIngredientWrapper *ingredient);
  void wrapperChanged();
  void updatedDisplay();
};

#endif
