#include "factorymanager.h"

FactoryManager::FactoryManager(QObject *parent)
    : FactoryManager(new ProfileFactory, new IngredientFactory,
                     new RecipeIngredientFactory, new RecipeFactory, parent) {}

FactoryManager::FactoryManager(ProfileFactory *p, IngredientFactory *i,
                               RecipeIngredientFactory *ri, RecipeFactory *r,
                               QObject *parent)
    : m_p(p), m_i(i), m_ri(ri), m_r(r), QObject(parent) {
  m_p->setParent(this);
  m_i->setParent(this);
  m_ri->setParent(this);
  m_r->setParent(this);

  connect(m_p, &ProfileFactory::objectCreated, this,
          &FactoryManager::onObjectCreation);
  connect(m_p, &ProfileFactory::objectLoaded, this,
          &FactoryManager::onObjectLoad);

  connect(m_i, &IngredientFactory::objectCreated, this,
          &FactoryManager::onObjectCreation);
  connect(m_i, &IngredientFactory::objectLoaded, this,
          &FactoryManager::onObjectLoad);

  connect(m_ri, &RecipeIngredientFactory::objectCreated, this,
          &FactoryManager::onObjectCreation);
  connect(m_ri, &RecipeIngredientFactory::objectLoaded, this,
          &FactoryManager::onObjectLoad);

  connect(m_r, &RecipeFactory::objectCreated, this,
          &FactoryManager::onObjectCreation);
  connect(m_r, &RecipeFactory::objectLoaded, this,
          &FactoryManager::onObjectLoad);
}

void FactoryManager::onObjectCreation(ObjectTypes type, Storable *object) {
  emit objectCreated(type, object);
}

void FactoryManager::onObjectLoad(ObjectTypes type, Storable *object) {
  emit objectLoaded(type, object);
}

void FactoryManager::onFormSubmitted(ObjectTypes type,
                                     const QVariantMap &data) {
  switch (type) {
  case PROFILEOBJECT:
    m_p->createObject(data);
    break;
  case INGREDIENTOBJECT:
    m_i->createObject(data);
    break;
  case RECIPEINGREDIENTOBJECT:
    m_ri->createObject(data);
    break;
  case RECIPEOBJECT:
    m_r->createObject(data);
    break;
  }
}

void FactoryManager::onDataLoaded(ObjectTypes type, const QVariantMap &data) {
  switch (type) {
  case PROFILEOBJECT:
    m_p->loadObject(data);
    break;
  case INGREDIENTOBJECT:
    m_i->loadObject(data);
    break;
  case RECIPEINGREDIENTOBJECT:
    m_ri->loadObject(data);
    break;
  case RECIPEOBJECT:
    m_r->loadObject(data);
    break;
  }
}

void FactoryManager::onDataLoaded(ObjectTypes type,
                                  const QList<QVariantMap> &data) {
  for (const QVariantMap &objectData : data) {
    onDataLoaded(type, objectData);
  }
}
