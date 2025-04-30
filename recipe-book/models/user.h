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
  const std::string &getPasswordHash() const;
  const std::vector<Recipe> &getSharedRecipes() const;

  void setUsername(const std::string &username);
  void setPasswordHash(const std::string &password_hash);
  void addSharedRecipe(Recipe recipe);
  void removeSharedRecipe(Recipe recipe);

  bool authenticate(const std::string &password_hash) const;
};

#endif
