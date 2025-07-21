#ifndef RECIPEFACTORY_H
#define RECIPEFACTORY_H

#include "genericfactory.h"
#include "qrecipe.h"

#include <QVariantMap>

class RecipeFactory : public GenericFactory<QRecipe> {
  Q_OBJECT

public:
  explicit RecipeFactory(QObject *parent = nullptr);

  QRecipe *createObject(const QVariantMap &data) override;
  QRecipe *loadObject(const QVariantMap &data) override;

signals:
  void recipeCreated(QRecipe *);
  void recipeLoaded(QRecipe *);
};

#endif
