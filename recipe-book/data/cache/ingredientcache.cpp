#include "ingredientcache.h"

IngredientCache::IngredientCache(QObject *parent)
    : StorableObjectCache<QIngredient>(parent) {}

QIngredient *IngredientCache::getIngredientByName(const QString &name) {
  for (Storable *ingredient : m_objectCache) {
    if (qobject_cast<QIngredient *>(ingredient)->getName() == name) {
      return qobject_cast<QIngredient *>(ingredient);
    }
  }

  return nullptr;
}
