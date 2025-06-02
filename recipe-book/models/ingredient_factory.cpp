#include "ingredient_factory.h"

IngredientFactory::IngredientFactory(QObject *parent) : QObject(parent) {}

void IngredientFactory::ingredientFormSubmitted(const QVariantMap &data) {
  QString name = data.value("name").toString();
  QString description = data.value("description").toString();

  // Notify about the new ingredient (parent set to nullptr so receiver can
  // manage it)
  emit createdNewIngredient(new QtIngredientWrapper(name, description));
}
