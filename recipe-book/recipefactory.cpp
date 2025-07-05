#include "recipefactory.h"

RecipeFactory::RecipeFactory(QObject *parent) : QObject{parent} {}

void RecipeFactory::createRecipe(QProfile *currentUser, const QString &name,
                                 const QString &description, quint32 prepTime,
                                 const QList<QRecipeIngredient *> &ingredients,
                                 const QStringList &instructions,
                                 const QStringList &equipment) {

  // No parent so that the widget can take ownership
  QRecipe *newRecipe = new QRecipe(name, description, ingredients, instructions,
                                   equipment, "", prepTime);
  newRecipe->setCreator(currentUser);

  emit recipeCreated(newRecipe);
}
