#ifndef FACTORYMANAGER_H
#define FACTORYMANAGER_H

#include "../objecttypes.h"
#include "ingredientfactory.h"
#include "profilefactory.h"
#include "recipefactory.h"
#include "recipeingredientfactory.h"

#include <QObject>
#include <qcontainerfwd.h>

class FactoryManager : public QObject {
  Q_OBJECT

  ProfileFactory *m_p;
  IngredientFactory *m_i;
  RecipeIngredientFactory *m_ri;
  RecipeFactory *m_r;

public:
  // We set the ownership of all the factories to this object in the constructor
  explicit FactoryManager(QObject *parent = nullptr);
  explicit FactoryManager(
      ProfileFactory *p = new ProfileFactory(),
      IngredientFactory *i = new IngredientFactory(),
      RecipeIngredientFactory *ri = new RecipeIngredientFactory(),
      RecipeFactory *r = new RecipeFactory(), QObject *parent = nullptr);

private slots:
  void
  onObjectCreation(ObjectTypes type,
                   Storable *object); // Save to database, invalidate relevant
                                      // cache query, send to the UI
  void onObjectLoad(ObjectTypes type,
                    Storable *object); // Simply send to the ui

public slots:
  void onFormSubmitted(ObjectTypes type, const QVariantMap &data);
  void onDataLoaded(ObjectTypes type, const QVariantMap &data);
  void onDataLoaded(ObjectTypes type, const QList<QVariantMap> &data);

signals:
  void objectCreated(ObjectTypes type, Storable *object);
  void objectLoaded(ObjectTypes type, Storable *object);
};

#endif
