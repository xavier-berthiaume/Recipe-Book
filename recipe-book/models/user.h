#ifndef USER_H
#define USER_H

#include "recipe.h"

#include <string>
#include <vector>

class User {
  std::string username;
  std::string password_hash;
  std::vector<Recipe> shared_recipes;

public:
  const std::string &getUsername() const;
  const std::vector<Recipe> &getSharedRecipes() const;

  void setUsername(const std::string &username);
  void setPassword(const std::string &plain_password);
  void addSharedRecipe(Recipe recipe);
  void removeSharedRecipe(Recipe recipe);

  bool authenticate(const std::string &password) const;
};

#endif

