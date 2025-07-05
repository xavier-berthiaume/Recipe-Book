#ifndef INGREDIENTFACTORY_H
#define INGREDIENTFACTORY_H

#include <QDebug>
#include <QObject>

#include "qingredient.h"

class IngredientFactory : public QObject {
  Q_OBJECT

public:
  explicit IngredientFactory(QObject *parent = nullptr);

  void createIngredient(QProfile *currentUser, const QString &name,
                        const QString &description);

signals:
  void ingredientCreated(QIngredient *newIngredient);
};

#endif // INGREDIENTFACTORY_H
