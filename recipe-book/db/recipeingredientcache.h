#ifndef RECIPEINGREDIENTCACHE_H
#define RECIPEINGREDIENTCACHE_H

#include "storableobjectcache.h"

class RecipeIngredientCache : public StorableObjectCache<QRecipeIngredient> {
  Q_OBJECT

public:
  explicit RecipeIngredientCache(QObject *parent = nullptr);
};

#endif
