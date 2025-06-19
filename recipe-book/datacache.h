#ifndef DATACACHE_H
#define DATACACHE_H

#include <QObject>
#include <QList>

#include "qprofile.h"
#include "qingredient.h"

class DataCache : public QObject
{
    Q_OBJECT

    QProfile *m_selectedProfile;
    QList<QProfile *> m_profilesCache;
    QList<QIngredient *> m_ingredientsCache;

    // Objects to remove from the database
    QList<QProfile *> m_profilesToRemove;
    QList<QIngredient *> m_ingredientsToRemove;

public:
    explicit DataCache(QObject *parent = nullptr);

    QProfile *getSelectedProfile() const;
    QList<QProfile *> getProfileCache() const;
    QList<QIngredient *> getIngredientCache() const;

    void setSelectedProfile(QProfile *);
    void addProfileToCache(QProfile *);
    void removeProfileFromCache(QProfile *);
    void addIngredientToCache(QIngredient *);
    void removeIngredientFromCache(QIngredient *);

signals:
    void selectedProfileChanged(QProfile *);
    void profileAdded(QProfile *);
    void profileRemoved(QProfile *);
    void profileCacheChanged();
    void ingredientAdded(QIngredient *);
    void ingredientRemoved(QIngredient *);
    void ingredientCacheChanged();
};

#endif // DATACACHE_H
