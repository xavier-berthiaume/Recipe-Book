#ifndef INGREDIENT_FACTORY_H
#define INGREDIENT_FACTORY_H

#include "qt_ingredient_wrapper.h"

#include <QObject>
#include <QVariantMap>

class IngredientFactory : public QObject {
  Q_OBJECT

public:
  explicit IngredientFactory(QObject *parent = nullptr);

public slots:
  void ingredientFormSubmitted(const QVariantMap &data);

signals:
  void createdNewIngredient(QtIngredientWrapper *newIngredient);
};

#endif
