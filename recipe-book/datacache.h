#ifndef DATACACHE_H
#define DATACACHE_H

#include <QList>
#include <QObject>
#include <qobject.h>

#include "qingredient.h"
#include "qprofile.h"
#include "qrecipe.h"

class DataCache : public QObject {
  Q_OBJECT

  QProfile *m_selectedProfile;
  QList<QProfile *> m_profilesCache;
  QList<QIngredient *> m_ingredientsCache;
  QList<QRecipe *> m_recipesCache;

  QList<QObject *> m_modelsToSave;
  QList<QObject *> m_modelsToUpdate;
  QList<QObject *> m_modelsToRemove;

public:
  explicit DataCache(QObject *parent = nullptr);

  QProfile *getSelectedProfile() const;
  QList<QProfile *> getProfileCache() const;
  QList<QIngredient *> getIngredientCache() const;
  QList<QRecipe *> getRecipeCache() const;

  QList<QObject *> getModelsToSave() const;
  QList<QObject *> getModelsToUpdate() const;
  QList<QObject *> getModelsToDelete() const;

  void setSelectedProfile(QProfile *);

  void initializeProfileCache(const QList<QObject *> &);
  void initializeProfileCache(const QList<QProfile *> &);
  void addProfileToCache(QProfile *);
  void removeProfileFromCache(QProfile *);

  void initializeIngredientCache(const QList<QObject *> &);
  void initializeIngredientCache(const QList<QIngredient *> &);
  void addIngredientToCache(QIngredient *);
  void removeIngredientFromCache(QIngredient *);

  void initializeRecipeCache(const QList<QObject *> &);
  void initializeRecipeCache(const QList<QRecipe *> &);
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
