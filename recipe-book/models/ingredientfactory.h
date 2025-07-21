#ifndef INGREDIENTFACTORY_H
#define INGREDIENTFACTORY_H

#include "genericfactory.h"
#include "qingredient.h"

#include <QVariantMap>

class IngredientFactory : GenericFactory<QIngredient> {
  Q_OBJECT

public:
  explicit IngredientFactory(QObject *parent = nullptr);

  QIngredient *createObject(const QVariantMap &data) override;
  QIngredient *loadObject(const QVariantMap &data) override;

signals:
  void ingredientCreated(QIngredient *);
  void ingredientLoaded(QIngredient *);
};

#endif
