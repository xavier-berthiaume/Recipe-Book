#include "datacache.h"

#include <QDebug>
#include <QPair>

DataCache::DataCache(QObject *parent)
    : QObject{parent}, m_selectedProfile(nullptr) {}

QProfile *DataCache::getSelectedProfile() const { return m_selectedProfile; }

QList<QProfile *> DataCache::getProfileCache() const { return m_profilesCache; }

QList<QIngredient *> DataCache::getIngredientCache() const {
  return m_ingredientsCache;
}

void DataCache::setSelectedProfile(QProfile *profile) {
  if (m_selectedProfile != profile) {
    m_selectedProfile = profile;
    QString profileName =
        (profile == nullptr) ? "No profile" : profile->getUsername();
    qDebug() << "Switched selected profile to: " << profileName;
    emit selectedProfileChanged(profile);
  }
}

void DataCache::initializeProfileCache(const QList<QObject *> &profiles) {
  for (QObject *obj : profiles) {
    if (QProfile *profile = qobject_cast<QProfile *>(obj)) {
      profile->setParent(this);
      m_profilesCache.push_back(profile);
    } else {
      qWarning() << "Trying to add a QObject that can't be cast to profile to "
                    "the profile cache";
    }
  }
}

void DataCache::initializeProfileCache(const QList<QProfile *> &profiles) {
  for (QProfile *profile : profiles) {
    profile->setParent(this);
  }

  m_profilesCache = profiles;
}

void DataCache::addProfileToCache(QProfile *profile) {
  if (!profile || m_profilesCache.contains(profile)) {
    return;
  }

  if (m_profilesCache.size() == 1 && m_selectedProfile == nullptr) {
    setSelectedProfile(m_profilesCache.at(0));
  }

  m_profilesCache.append(profile);
  m_modelsToSave.append(profile);
  qDebug() << "Added profile to cache: " << profile->getUsername();
  emit profileAdded(profile);
  emit profileCacheChanged();
}

void DataCache::removeProfileFromCache(QProfile *profile) {
  if (!profile || !m_profilesCache.contains(profile)) {
    qDebug() << "No profile or profile isn't in cache";
    return;
  }

  m_profilesCache.removeOne(profile);
  qDebug() << "Removed profile from cache: " << profile->getUsername();
  m_modelsToRemove.append(profile);
  qDebug() << "Marking profile for deletion: " << profile->getUsername();

  if (m_selectedProfile == profile) {
    setSelectedProfile(nullptr);
    qDebug() << "Deleted profile was set as selected, removing...";
  }

  emit profileRemoved(profile);
  emit profileCacheChanged();
}

void DataCache::initializeIngredientCache(const QList<QObject *> &ingredients) {
  for (QObject *obj : ingredients) {
    if (QIngredient *ingredient = qobject_cast<QIngredient *>(obj)) {
      ingredient->setParent(this);
      m_ingredientsCache.push_back(ingredient);
    } else {
      qWarning() << "Trying to add a QObject that can't be cast to ingredient "
                    "to the ingredient cache";
    }
  }
}

void DataCache::initializeIngredientCache(
    const QList<QIngredient *> &ingredients) {
  for (QIngredient *ingredient : ingredients) {
    ingredient->setParent(this);
  }

  m_ingredientsCache = ingredients;
}

void DataCache::addIngredientToCache(QIngredient *ingredient) {
  if (!ingredient || m_ingredientsCache.contains(ingredient)) {
    return;
  }

  m_ingredientsCache.append(ingredient);
  m_modelsToSave.append(ingredient);
  qDebug() << "Added ingredient to cache: " << ingredient->getName();
  emit ingredientAdded(ingredient);
  emit ingredientCacheChanged();
}

void DataCache::removeIngredientFromCache(QIngredient *ingredient) {
  if (!ingredient || !m_ingredientsCache.contains(ingredient)) {
    qDebug() << "No ingredient or ingredient isn't in cache";
    return;
  }

  m_ingredientsCache.removeOne(ingredient);
  qDebug() << "Removed ingredient from cache: " << ingredient->getName();
  m_modelsToRemove.append(ingredient);
  qDebug() << "Marking ingredient for deletion: " << ingredient->getName();

  emit ingredientRemoved(ingredient);
  emit ingredientCacheChanged();
}

QList<QRecipe *> DataCache::getRecipeCache() const { return m_recipesCache; }

void DataCache::initializeRecipeCache(const QList<QObject *> &recipes) {
  for (QObject *obj : recipes) {
    if (QRecipe *recipe = qobject_cast<QRecipe *>(obj)) {
      recipe->setParent(this);
      m_recipesCache.push_back(recipe);
    } else {
      qWarning() << "Trying to add a QObject that can't be cast to recipe to "
                    "the recipe cache";
    }
  }
}

QList<QObject *> DataCache::getModelsToSave() const { return m_modelsToSave; }

QList<QObject *> DataCache::getModelsToUpdate() const {
  return m_modelsToUpdate;
}

QList<QObject *> DataCache::getModelsToDelete() const {
  return m_modelsToRemove;
}

void DataCache::initializeRecipeCache(const QList<QRecipe *> &recipes) {
  for (QRecipe *recipe : recipes) {
    recipe->setParent(this);
  }

  m_recipesCache = recipes;
}

void DataCache::addRecipeToCache(QRecipe *recipe) {
  if (!recipe || m_recipesCache.contains(recipe)) {
    return;
  }

  m_recipesCache.append(recipe);
  m_modelsToSave.append(recipe);
  qDebug() << "Added recipe to cache" << recipe->getName();
  emit recipeAdded(recipe);
  emit recipeCacheChanged();
}

void DataCache::removeRecipeFromCache(QRecipe *recipe) {
  if (!recipe || !m_recipesCache.contains(recipe)) {
    qDebug() << "No recipe or recipe isn't in cache";
    return;
  }

  m_recipesCache.removeOne(recipe);
  qDebug() << "Removed recipe from cache: " << recipe->getName();
  m_modelsToRemove.append(recipe);
  qDebug() << "Marking recipe for deletion:" << recipe->getName();

  emit recipeRemoved(recipe);
  emit recipeCacheChanged();
}
