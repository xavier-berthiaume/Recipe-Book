#ifndef INGREDIENT_ROOT_VIEW_H
#define INGREDIENT_ROOT_VIEW_H

#include "../models/ingredient_factory.h"
#include "../models/qt_ingredient_wrapper.h"
#include "generic_root_view.h"

class IngredientRootView : public GenericRootView<QtIngredientWrapper> {
  Q_OBJECT

  IngredientFactory *m_ingredientFactory;

protected:
  void displayModels() override;

public:
  explicit IngredientRootView(const QList<QtIngredientWrapper *> &models,
                              QWidget *parent = nullptr);

  void setFactory(IngredientFactory *factory);

private slots:
  void displayBoxClicked(QtIngredientWrapper *ingredient);
  void searchButtonClicked();
  void createButtonClicked();
  void updateView();

public slots:
  void newIngredient(QtIngredientWrapper *ingredient);

signals:
  void ingredientClicked(QtIngredientWrapper *ingredient);
};
#endif
