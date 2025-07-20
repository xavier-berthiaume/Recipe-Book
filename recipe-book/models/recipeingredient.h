#ifndef RECIPEINGREDIENT_H
#define RECIPEINGREDIENT_H

#include <string>

class RecipeIngredient {
  std::string m_ingredientId;
  std::string m_unit;
  double m_quantity;

public:
  RecipeIngredient(const std::string &ingredientId, const std::string &unit,
                   double quantity);

  std::string getIngredientId() const;
  std::string getUnit() const;
  double getQuantity() const;

  void setIngredientId(const std::string &ingredientId);
  void setUnit(const std::string &unit);
  void setQuantity(double quantity);
};

#endif
