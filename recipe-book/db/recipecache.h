#ifndef RECIPECACHE_H
#define RECIPECACHE_H

#include "storableobjectcache.h"

class RecipeCache : public StorableObjectCache<QRecipe> {
  Q_OBJECT

public:
  explicit RecipeCache(QObject *parent = nullptr);

  QRecipe *getRecipeByName(const QString &name);
};

#endif
