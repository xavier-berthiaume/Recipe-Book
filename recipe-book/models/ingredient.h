#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {

  std::string name;
  std::string description;
  bool is_recipe;
  std::string linked_recipe_id;

public:
  Ingredient();
  Ingredient(const std::string &name, const std::string &description,
             bool is_recipe, const std::string &linked_recipe_id);

  std::string getName() const;
  std::string getDescription() const;
  bool getIsRecipe() const;
  std::string getLinkedRecipeId() const;

  void setName(const std::string &name);
  void setDescription(std::string &description);
  void setIsRecipe(bool is_recipe);
  void setLinkedRecipeId(const std::string &linked_recipe_id);
};

#endif
