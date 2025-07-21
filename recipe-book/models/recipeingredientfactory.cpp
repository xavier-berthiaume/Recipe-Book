#include "recipeingredientfactory.h"
#include "qrecipeingredient.h"

RecipeIngredientFactory::RecipeIngredientFactory(QObject *parent)
    : GenericFactory<QRecipeIngredient>(parent) {}

QRecipeIngredient *
RecipeIngredientFactory::createObject(const QVariantMap &data) {

  QRecipeIngredient *newRI = new QRecipeIngredient(
      data["ingredientId"].toUuid(), data["unit"].value<Units>(),
      data["quantity"].toDouble());

  emit recipeIngredientCreated(newRI);
  return newRI;
}

QRecipeIngredient *
RecipeIngredientFactory::loadObject(const QVariantMap &data) {

  QRecipeIngredient *newRI = new QRecipeIngredient(
      data["id"].toUuid(), data["ingredientId"].toUuid(),
      data["unit"].value<Units>(), data["quantity"].toDouble());

  emit recipeIngredientLoaded(newRI);
  return newRI;
}
