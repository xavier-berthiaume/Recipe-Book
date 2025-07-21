#include "ingredientfactory.h"
#include "qingredient.h"

IngredientFactory::IngredientFactory(QObject *parent)
    : GenericFactory<QIngredient>(parent) {}

QIngredient *IngredientFactory::createObject(const QVariantMap &data) {

  QIngredient *newIngredient =
      new QIngredient(data["creatorId"].toUuid(), data["name"].toString(),
                      data["description"].toString(), this);

  emit ingredientCreated(newIngredient);
  return newIngredient;
}

QIngredient *IngredientFactory::loadObject(const QVariantMap &data) {
  QIngredient *newIngredient = new QIngredient(
      data["id"].toUuid(), data["creatorId"].toUuid(), data["name"].toString(),
      data["description"].toString(), this);

  emit ingredientLoaded(newIngredient);
  return newIngredient;
}
