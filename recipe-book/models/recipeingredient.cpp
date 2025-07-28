#include "recipeingredient.h"

RecipeIngredient::RecipeIngredient(const std::string &ingredientId,
                                   const std::string &unit, double quantity,
                                   bool isRecipe)
    : m_ingredientId(ingredientId), m_unit(unit), m_quantity(quantity),
      m_isRecipe(isRecipe) {}

std::string RecipeIngredient::getIngredientId() const { return m_ingredientId; }

std::string RecipeIngredient::getUnit() const { return m_unit; }

double RecipeIngredient::getQuantity() const { return m_quantity; }

bool RecipeIngredient::getIsRecipe() const { return m_isRecipe; }

void RecipeIngredient::setIngredientId(const std::string &ingredientId) {
  m_ingredientId = ingredientId;
}

void RecipeIngredient::setUnit(const std::string &unit) { m_unit = unit; }

void RecipeIngredient::setQuantity(double quantity) { m_quantity = quantity; }

void RecipeIngredient::setIsRecipe(bool isRecipe) { m_isRecipe = isRecipe; }
