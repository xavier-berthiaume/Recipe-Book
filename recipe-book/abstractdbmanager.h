#ifndef ABSTRACTDBMANAGER_H
#define ABSTRACTDBMANAGER_H

#include "ingredientfactory.h"
#include "profilefactory.h"
#include "recipefactory.h"
#include "recipeingredientfactory.h"

#include <QObject>

class AbstractDbManager : public QObject {
  Q_OBJECT

protected:
  ProfileFactory *m_profileFactory;
  IngredientFactory *m_ingredientFactory;
  RecipeIngredientFactory *m_recipeingredientFactory;
  RecipeFactory *m_recipeFactory;

public:
  explicit AbstractDbManager(
      ProfileFactory *profileFactory = nullptr,
      IngredientFactory *ingredientFactory = nullptr,
      RecipeIngredientFactory *recipeingredientFactory = nullptr,
      RecipeFactory *recipeFactory = nullptr, QObject *parent = nullptr);

  // Must be virtual so that the destructor of the derived classes are called
  virtual ~AbstractDbManager() = default;

  enum ObjectType {
    ProfileType,
    IngredientType,
    RecipeIngredientType,
    RecipeType
  };

  virtual bool saveObject(QObject *object) = 0;
  virtual bool updateObject(QObject *object) = 0;
  virtual QObject *readObject(const QString &objectType, const QUuid &id) = 0;
  // This signature is meant to provide a single use function that loads all
  // objects of a given type. In truth, its implementation kind of sucks since
  // you have to cast objects twice: once after being loaded from the database
  // to the QObject * type, then a second time to their actual type. I'm not
  // sure what better implementation I can come up with at the moment. Perhaps
  // using the visitor pattern is more appropriate...
  virtual bool readAllObjects(ObjectType type, QList<QObject *> &objects) = 0;
  virtual bool deleteObject(const QString &objectType, const QUuid &id) = 0;

  virtual bool beginTransaction() = 0;
  virtual bool commitTransaction() = 0;
  virtual bool rollbackTransaction() = 0;
};

#endif
