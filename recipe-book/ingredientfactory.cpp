#include "ingredientfactory.h"
#include "qingredient.h"

IngredientFactory::IngredientFactory(QObject *parent) : QObject{parent} {}

void IngredientFactory::createIngredient(QProfile *currentUser,
                                         const QString &name,
                                         const QString &description) {
  if (name.isEmpty() || description.isEmpty())
    return;

  if (currentUser == nullptr) {
    qWarning() << "No profile currently set";
    return;
  }

  QIngredient *newIngredient = new QIngredient(name, description);
  newIngredient->setCreator(currentUser);
  qDebug() << "Created new ingredient with name " << newIngredient->getName();
  emit ingredientCreated(newIngredient);
}

QIngredient *IngredientFactory::loadIngredient(const QUuid &id,
                                               QProfile *creator,
                                               const QString &name,
                                               const QString &description) {
  QIngredient *loadedIngredient = new QIngredient(id);
  loadedIngredient->setCreator(creator);
  creator->setParent(loadedIngredient);
  loadedIngredient->setName(name);
  loadedIngredient->setDescription(description);

  return loadedIngredient;
}
