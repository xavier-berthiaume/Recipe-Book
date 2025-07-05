#include "datacache.h"

#include <QDebug>

DataCache::DataCache(QObject *parent)
    : QObject{parent}
    , m_selectedProfile(nullptr)
{}

QProfile *DataCache::getSelectedProfile() const {
    return m_selectedProfile;
}

QList<QProfile *> DataCache::getProfileCache() const {
    return m_profilesCache;
}

QList<QIngredient *> DataCache::getIngredientCache() const {
    return m_ingredientsCache;
}

void DataCache::setSelectedProfile(QProfile *profile) {
    if (m_selectedProfile != profile) {
        m_selectedProfile = profile;
        QString profileName = (profile == nullptr) ? "No profile" : profile->getUsername();
        qDebug() << "Switched selected profile to: " << profileName;
        emit selectedProfileChanged(profile);
    }
}

void DataCache::addProfileToCache(QProfile *profile) {
    if (!profile || m_profilesCache.contains(profile)) {
        return;
    }

    if (m_profilesCache.size() == 1 && m_selectedProfile == nullptr) {
        setSelectedProfile(m_profilesCache.at(0));
    }

    m_profilesCache.append(profile);
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

    if (!m_profilesToRemove.contains(profile)) {
        m_profilesToRemove.append(profile);
        qDebug() << "Marking profile for deletion: " << profile->getUsername();
    }

    if (m_selectedProfile == profile) {
        setSelectedProfile(nullptr);
        qDebug() << "Deleted profile was set as selected, removing...";
    }

    emit profileRemoved(profile);
    emit profileCacheChanged();
}


void DataCache::addIngredientToCache(QIngredient *ingredient) {
    if (!ingredient || m_ingredientsCache.contains(ingredient)) {
        return;
    }

    m_ingredientsCache.append(ingredient);
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

    if (!m_ingredientsToRemove.contains(ingredient)) {
        m_ingredientsToRemove.append(ingredient);
        qDebug() << "Marking ingredient for deletion: " << ingredient->getName();
    }

    emit ingredientRemoved(ingredient);
    emit ingredientCacheChanged();
}

QList<QRecipe *> DataCache::getRecipeCache() const {
    return m_recipesCache;
}

void DataCache::addRecipeToCache(QRecipe *recipe) {
    if (!recipe || m_recipesCache.contains(recipe)) {
        return;
    }

    m_recipesCache.append(recipe);
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

    if (!m_recipesToRemove.contains(recipe)) {
        m_recipesToRemove.append(recipe);
        qDebug() << "Marking recipe for deletion:" << recipe->getName();
    }

    emit recipeRemoved(recipe);
    emit recipeCacheChanged();
}
