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

  void updateDisplay() override;

public:
  explicit IngredientDisplayBox(QWidget *parent = nullptr);

  void setWrapper(QtIngredientWrapper *wrapper) override;

signals:
  void wrapperChanged();
};

#endif
