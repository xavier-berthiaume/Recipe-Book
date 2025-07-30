#include "recipeingredientfactory.h"
#include "qrecipeingredient.h"

RecipeIngredientFactory::RecipeIngredientFactory(QObject *parent)
    : GenericFactory<QRecipeIngredient>(parent) {}

QRecipeIngredient *
RecipeIngredientFactory::createObject(const QVariantMap &data) {

  QRecipeIngredient *newRI = new QRecipeIngredient(
      data["ingredientId"].toUuid(), data["unit"].value<Units>(),
      data["quantity"].toDouble(), data["isRecipe"].toBool());

  emit objectCreated(RECIPEINGREDIENTOBJECT, newRI);
  emit recipeIngredientCreated(newRI);
  return newRI;
}

QRecipeIngredient *
RecipeIngredientFactory::loadObject(const QVariantMap &data) {

  QRecipeIngredient *loadedRI = new QRecipeIngredient(
      data["id"].toUuid(), data["ingredientId"].toUuid(),
      data["unit"].value<Units>(), data["quantity"].toDouble(),
      data["isRecipe"].toBool());

  emit objectLoaded(RECIPEINGREDIENTOBJECT, loadedRI);
  emit recipeIngredientLoaded(loadedRI);
  return loadedRI;
}
