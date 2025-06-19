#include "datacache.h"

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
        emit selectedProfileChanged(profile);
    }
}

void DataCache::addProfileToCache(QProfile *profile) {
    if (!profile || m_profilesCache.contains(profile)) {
        return;
    }

    m_profilesCache.append(profile);
    emit profileAdded(profile);
    emit profileCacheChanged();
}

void DataCache::removeProfileFromCache(QProfile *profile) {
    if (!profile || !m_profilesCache.contains(profile)) {
        return;
    }

    m_profilesCache.removeOne(profile);

    if (!m_profilesToRemove.contains(profile)) {
        m_profilesToRemove.append(profile);
    }

    if (m_selectedProfile == profile) {
        setSelectedProfile(nullptr);
    }

    emit profileRemoved(profile);
    emit profileCacheChanged();
}


void DataCache::addIngredientToCache(QIngredient *ingredient) {
    if (!ingredient || m_ingredientsCache.contains(ingredient)) {
        return;
    }

    m_ingredientsCache.append(ingredient);
    emit ingredientAdded(ingredient);
    emit ingredientCacheChanged();
}

void DataCache::removeIngredientFromCache(QIngredient *ingredient) {
    if (!ingredient || !m_ingredientsCache.contains(ingredient)) {
        return;
    }

    m_ingredientsCache.removeOne(ingredient);

    if (!m_ingredientsToRemove.contains(ingredient)) {
        m_ingredientsToRemove.append(ingredient);
    }

    emit ingredientRemoved(ingredient);
    emit ingredientCacheChanged();
}
