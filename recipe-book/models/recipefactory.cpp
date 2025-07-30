#include "recipefactory.h"

RecipeFactory::RecipeFactory(QObject *parent)
    : GenericFactory<QRecipe>(parent) {}

QRecipe *RecipeFactory::createObject(const QVariantMap &data) {

  QList<QUuid> ingredientIds;
  QVariantList idList = data["recipeIngredientIds"].toList();
  for (const QVariant &idVar : idList) {
    ingredientIds.append(idVar.toUuid());
  }

  QRecipe *newRecipe = new QRecipe(
      data["creatorId"].toUuid(), data["name"].toString(),
      data["description"].toString(), data["notes"].toString(), ingredientIds,
      data["instructions"].toStringList(), data["equipment"].toStringList(),
      data["prepTime"].toDouble(), this);

  emit objectCreated(RECIPEOBJECT, newRecipe);
  emit recipeCreated(newRecipe);
  return newRecipe;
}

QRecipe *RecipeFactory::loadObject(const QVariantMap &data) {

  QList<QUuid> ingredientIds;
  QVariantList idList = data["recipeIngredientIds"].toList();
  for (const QVariant &idVar : idList) {
    ingredientIds.append(idVar.toUuid());
  }

  QRecipe *loadedRecipe = new QRecipe(
      data["id"].toUuid(), data["creatorId"].toUuid(), data["name"].toString(),
      data["description"].toString(), data["notes"].toString(), ingredientIds,
      data["instructions"].toStringList(), data["equipment"].toStringList(),
      data["prepTime"].toDouble(), this);

  emit objectLoaded(RECIPEOBJECT, loadedRecipe);
  emit recipeLoaded(loadedRecipe);
  return loadedRecipe;
}
