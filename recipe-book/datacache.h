#ifndef DATACACHE_H
#define DATACACHE_H

#include <QObject>
#include <QList>

#include "qprofile.h"
#include "qingredient.h"
#include "qrecipe.h"

class DataCache : public QObject
{
    Q_OBJECT

    QProfile *m_selectedProfile;
    QList<QProfile *> m_profilesCache;
    QList<QIngredient *> m_ingredientsCache;
    QList<QRecipe *> m_recipesCache;

    // Objects to remove from the database
    QList<QProfile *> m_profilesToRemove;
    QList<QIngredient *> m_ingredientsToRemove;
    QList<QRecipe *> m_recipesToRemove;

public:
    explicit DataCache(QObject *parent = nullptr);

    QProfile *getSelectedProfile() const;
    QList<QProfile *> getProfileCache() const;
    QList<QIngredient *> getIngredientCache() const;
    QList<QRecipe *> getRecipeCache() const;

    void setSelectedProfile(QProfile *);
    void addProfileToCache(QProfile *);
    void removeProfileFromCache(QProfile *);
    void addIngredientToCache(QIngredient *);
    void removeIngredientFromCache(QIngredient *);
    void addRecipeToCache(QRecipe *);
    void removeRecipeFromCache(QRecipe *);

signals:
    void selectedProfileChanged(QProfile *);
    void profileAdded(QProfile *);
    void profileRemoved(QProfile *);
    void profileCacheChanged();
    void ingredientAdded(QIngredient *);
    void ingredientRemoved(QIngredient *);
    void ingredientCacheChanged();
    void recipeAdded(QRecipe *);
    void recipeRemoved(QRecipe *);
    void recipeCacheChanged();
};

#endif // DATACACHE_H
