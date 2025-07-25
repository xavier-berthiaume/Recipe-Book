#include "recipeingredientcache.h"

RecipeIngredientCache::RecipeIngredientCache(QObject *parent)
    : StorableObjectCache<QRecipeIngredient>(parent) {}
