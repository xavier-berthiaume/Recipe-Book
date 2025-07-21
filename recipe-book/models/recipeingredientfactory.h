#ifndef RECIPEINGREDIENTFACTORY_H
#define RECIPEINGREDIENTFACTORY_H

#include "genericfactory.h"
#include "qrecipeingredient.h"

#include <QVariantMap>

class RecipeIngredientFactory : public GenericFactory<QRecipeIngredient> {
  Q_OBJECT

public:
  explicit RecipeIngredientFactory(QObject *parent = nullptr);

  QRecipeIngredient *createObject(const QVariantMap &data) override;
  QRecipeIngredient *loadObject(const QVariantMap &data) override;

signals:
  void recipeIngredientCreated(QRecipeIngredient *);
  void recipeIngredientLoaded(QRecipeIngredient *);
};

#endif
