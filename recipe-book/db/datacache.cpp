#include "datacache.h"

DataCache::DataCache(QObject *parent)
    : QObject(parent), m_profileCache(ProfileCache(this)),
      m_ingredientCache(IngredientCache(this)),
      m_riCache(RecipeIngredientCache(this)), m_recipeCache(RecipeCache(this)) {
}

QProfile *DataCache::getProfile(const QUuid &id) {
  return m_profileCache.getObjectInCache(id);
}

QProfile *DataCache::getProfile(const QString &username) {
  return m_profileCache.getProfileByName(username);
}

void DataCache::profileDeleted(const QUuid &id) {
  QProfile *profile = m_profileCache.getObjectInCache(id);
   
  
  // If no profile was found in cache, 
  if (profile == nullptr)
    return;


}

QIngredient *DataCache::getIngredient(const QUuid &id) {
  return m_ingredientCache.getObjectInCache(id);
}

QIngredient *DataCache::getIngredient(const QString &name) {
  return m_ingredientCache.getIngredientByName(name);
}

QRecipeIngredient *DataCache::getRecipeIngredient(const QUuid &id) {
  return m_riCache.getObjectInCache(id);
}

QRecipe *DataCache::getRecipe(const QUuid &id) {
  return m_recipeCache.getObjectInCache(id);
}

QRecipe *DataCache::getRecipe(const QString &name) {
  return m_recipeCache.getRecipeByName(name);
}
