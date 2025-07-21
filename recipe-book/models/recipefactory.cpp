#include "recipefactory.h"

RecipeFactory::RecipeFactory(QObject *parent)
    : GenericFactory<QRecipe>(parent) {}

QRecipe *RecipeFactory::createObject(const QVariantMap &data) {

  // TODO - EITHER PASS THE RECIPE INGREDIENT ID'S DIRECTLY IN THE FORM, OR PASS
  // THE OBJECTS IN THE FORM AND EXTRACT THE ID'S HERE. LEAVING AN EMPTY LIST
  // HERE AT THE MOMENT
  QRecipe *newRecipe = new QRecipe(
      data["creatorId"].toUuid(), data["name"].toString(),
      data["description"].toString(), data["notes"].toString(), QList<QUuid>(),
      data["instructions"].toStringList(), data["equipment"].toStringList(),
      data["prepTime"].toDouble(), this);

  emit recipeCreated(newRecipe);
  return newRecipe;
}

QRecipe *RecipeFactory::loadObject(const QVariantMap &data) {

  // TODO - EITHER PASS THE RECIPE INGREDIENT ID'S DIRECTLY IN THE FORM, OR PASS
  // THE OBJECTS IN THE FORM AND EXTRACT THE ID'S HERE. LEAVING AN EMPTY LIST
  // HERE AT THE MOMENT
  QRecipe *newRecipe = new QRecipe(
      data["id"].toUuid(), data["creatorId"].toUuid(), data["name"].toString(),
      data["description"].toString(), data["notes"].toString(), QList<QUuid>(),
      data["instructions"].toStringList(), data["equipment"].toStringList(),
      data["prepTime"].toDouble(), this);

  emit recipeLoaded(newRecipe);
  return newRecipe;
}
