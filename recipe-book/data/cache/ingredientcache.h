#ifndef INGREDIENTCACHE_H
#define INGREDIENTCACHE_H

#include "storableobjectcache.h"

class IngredientCache : public StorableObjectCache<QIngredient> {
  Q_OBJECT

public:
  explicit IngredientCache(QObject *parent = nullptr);

  QIngredient *getIngredientByName(const QString &name);
};

#endif
