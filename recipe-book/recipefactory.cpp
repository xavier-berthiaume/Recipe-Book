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

QRecipe *
RecipeFactory::loadRecipe(const QUuid &id, QProfile *creator,
                          const QString &name, const QString &description,
                          quint32 prepTime,
                          const QList<QRecipeIngredient *> &ingredients,
                          const QStringList &instructions,
                          const QStringList &equipment, const QString &notes) {
  QRecipe *loadedRecipe = new QRecipe(id);
  loadedRecipe->setCreator(creator);
  creator->setParent(loadedRecipe);
  loadedRecipe->setName(name);
  loadedRecipe->setDescription(description);
  loadedRecipe->setIngredients(ingredients);
  for (QRecipeIngredient *ing : ingredients) {
    ing->setParent(loadedRecipe);
  }
  loadedRecipe->setInstructions(instructions);
  loadedRecipe->setEquipment(equipment);
  loadedRecipe->setNotes(notes);

  return loadedRecipe;
}
