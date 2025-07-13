#include "abstractdbmanager.h"
#include "profilefactory.h"
#include "recipefactory.h"
#include "recipeingredientfactory.h"

AbstractDbManager::AbstractDbManager(
    ProfileFactory *profileFactory, IngredientFactory *ingredientFactory,
    RecipeIngredientFactory *recipeingredientFactory,
    RecipeFactory *recipeFactory, QObject *parent)
    : QObject(parent) {

  if (profileFactory == nullptr) {
    m_profileFactory = new ProfileFactory(this);
  } else {
    m_profileFactory = profileFactory;
  }

  if (ingredientFactory == nullptr) {
    m_ingredientFactory = new IngredientFactory(this);
  } else {
    m_ingredientFactory = ingredientFactory;
  }

  if (recipeingredientFactory == nullptr) {
    m_recipeingredientFactory = new RecipeIngredientFactory(this);
  } else {
    m_recipeingredientFactory = recipeingredientFactory;
  }

  if (recipeFactory == nullptr) {
    m_recipeFactory = new RecipeFactory(this);
  } else {
    m_recipeFactory = recipeFactory;
  }
}
