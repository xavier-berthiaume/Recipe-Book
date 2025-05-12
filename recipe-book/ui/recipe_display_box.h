#ifndef RECIPE_DISPLAY_BOX_H
#define RECIPE_DISPLAY_BOX_H

#include "../models//qt_recipe_wrapper.h"
#include "generic_object_display_box.h"

#include <QLabel>

class RecipeDisplayBox : public GenericObjectDisplayBox<QtRecipeWrapper> {
  Q_OBJECT

  QLabel *m_name_label;
  QLabel *m_details_label;
  QLabel *m_stats_label;

  void updateDisplay() override;

public:
  explicit RecipeDisplayBox(QWidget *parent = nullptr);

  void setWrapper(QtRecipeWrapper *wrapper) override;

signals:
  void wrapperChanged();
};

#endif
