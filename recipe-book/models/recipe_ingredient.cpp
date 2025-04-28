#include "recipe_ingredient.h"

RecipeIngredient::RecipeIngredient(QUuid recipe_id, QUuid ingredient_id,
                                   const QString &quantity, const QString &unit)
    : Storable(), recipe_id(recipe_id), ingredient_id(ingredient_id),
      quantity(quantity), unit(unit) {}

QUuid RecipeIngredient::getRecipeId() const { return recipe_id; }

QUuid RecipeIngredient::getIngredientId() const { return ingredient_id; }

const QString &RecipeIngredient::getQuantity() const { return quantity; }

const QString &RecipeIngredient::getUnit() const { return unit; }

void RecipeIngredient::setRecipeId(QUuid recipe_id) {
  this->recipe_id = recipe_id;
}

void RecipeIngredient::setIngredientId(QUuid ingredient_id) {
  this->ingredient_id = ingredient_id;
}

void RecipeIngredient::setQuantity(const QString &quantity) {
  this->quantity = quantity;
}

void RecipeIngredient::setUnit(const QString &unit) { this->unit = unit; }
