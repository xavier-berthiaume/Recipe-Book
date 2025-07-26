#ifndef DATACACHE_H
#define DATACACHE_H

#include "ingredientcache.h"
#include "profilecache.h"
#include "recipecache.h"
#include "recipeingredientcache.h"

#include <QObject>

class DataCache : public QObject {
  Q_OBJECT

  ProfileCache m_profileCache;
  IngredientCache m_ingredientCache;
  RecipeIngredientCache m_riCache;
  RecipeCache m_recipeCache;

public:
  explicit DataCache(QObject *parent = nullptr);

  QProfile *getProfile(const QUuid &id);
  QProfile *getProfile(const QString &username);
  void profileDeleted(const QUuid &id);

  QIngredient *getIngredient(const QUuid &id);
  QIngredient *getIngredient(const QString &name);
  void ingredientDeleted(const QUuid &id);

  QRecipeIngredient *getRecipeIngredient(const QUuid &id);

  QRecipe *getRecipe(const QUuid &id);
  QRecipe *getRecipe(const QString &name);
  void recipeDeleted(const QUuid &id);
};

#endif
