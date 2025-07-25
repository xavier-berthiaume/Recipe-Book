#include "recipecache.h"

RecipeCache::RecipeCache(QObject *parent)
    : StorableObjectCache<QRecipe>(parent) {}

QRecipe *RecipeCache::getRecipeByName(const QString &name) {
  for (Storable *recipe : m_objectCache) {
    if (qobject_cast<QRecipe *>(recipe)->getName() == name) {
      return qobject_cast<QRecipe *>(recipe);
    }
  }

  return nullptr;
}
