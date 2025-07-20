#include "recipeingredient.h"

RecipeIngredient::RecipeIngredient(const std::string &ingredientId,
                                   const std::string &unit, double quantity)
    : m_ingredientId(ingredientId), m_unit(unit), m_quantity(quantity) {}

std::string RecipeIngredient::getIngredientId() const { return m_ingredientId; }

std::string RecipeIngredient::getUnit() const { return m_unit; }

double RecipeIngredient::getQuantity() const { return m_quantity; }

void RecipeIngredient::setIngredientId(const std::string &ingredientId) {
  m_ingredientId = ingredientId;
}

void RecipeIngredient::setUnit(const std::string &unit) { m_unit = unit; }

void RecipeIngredient::setQuantity(double quantity) { m_quantity = quantity; }
