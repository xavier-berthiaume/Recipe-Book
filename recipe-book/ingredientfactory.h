#ifndef INGREDIENTFACTORY_H
#define INGREDIENTFACTORY_H

#include <QObject>
#include <QDebug>

#include "qingredient.h"

class IngredientFactory : public QObject
{
    Q_OBJECT

public:
    explicit IngredientFactory(QObject *parent = nullptr);

    void createIngredient(QProfile *currentUser, const QString &name, const QString &description);

signals:
    void ingredientCreated(QIngredient *newIngredient);
};

#endif // INGREDIENTFACTORY_H
