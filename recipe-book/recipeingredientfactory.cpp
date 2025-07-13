#include "recipeingredientfactory.h"

#include <QDebug>

RecipeIngredientFactory::RecipeIngredientFactory(QObject *parent)
    : QObject{parent} {}

void RecipeIngredientFactory::createRecipeIngredient(
    QIngredient *ingredient, const QString &quantity,
    QRecipeIngredient::Units unit, bool isRecipe) {

  QRecipeIngredient *newRecipeIngredient =
      new QRecipeIngredient(ingredient, quantity, unit);
  newRecipeIngredient->setIsRecipe(isRecipe);

  qDebug() << QString("Created RecipeIngredient %1 -> %2%3")
                  .arg(ingredient->getName(), quantity,
                       QRecipeIngredient::unitToString(unit));
  emit recipeIngredientCreated(newRecipeIngredient);
}

QRecipeIngredient *RecipeIngredientFactory::loadRecipeIngredient(
    const QUuid &id, QIngredient *ingredient, const QString &quantity,
    QRecipeIngredient::Units unit, bool isRecipe) {
  QRecipeIngredient *recipeIngredient = new QRecipeIngredient(id);
  recipeIngredient->setIngredient(ingredient);
  ingredient->setParent(recipeIngredient);
  recipeIngredient->setQuantity(quantity);
  recipeIngredient->setUnit(unit);
  recipeIngredient->setIsRecipe(isRecipe);

  return recipeIngredient;
}
