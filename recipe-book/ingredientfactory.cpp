#include "ingredientfactory.h"

IngredientFactory::IngredientFactory(QObject *parent)
    : QObject{parent}
{}

void IngredientFactory::createIngredient(QProfile *currentUser, const QString &name, const QString &description) {
    if (name.isEmpty() || description.isEmpty()) return;

    if (currentUser == nullptr) {
        qWarning() << "No profile currently set";
        return;
    }

    QIngredient *newIngredient = new QIngredient(name, description);
    newIngredient->setCreator(currentUser);
    qDebug() << "Created new ingredient with name " << newIngredient->getName();
    emit ingredientCreated(newIngredient);
}
