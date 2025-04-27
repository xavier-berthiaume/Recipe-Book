#include "user.h"

#include <algorithm> // For std::find

const std::string &User::getUsername() const { return username; }

const std::vector<Recipe> &User::getSharedRecipes() const {
  return shared_recipes;
}

void User::setUsername(const std::string &username) {
  this->username = username;
}

void User::setPassword(const std::string &plain_password) {
  // Hash the password, then set it
  this->password_hash = plain_password;
}

void User::addSharedRecipe(Recipe recipe) {
  shared_recipes.push_back(std::move(recipe));
}

void User::removeSharedRecipe(Recipe recipe) {
  auto it = std::find(shared_recipes.begin(), shared_recipes.end(), recipe);
  if (it != shared_recipes.end()) {
    shared_recipes.erase(it);
  }
}

bool User::authenticate(const std::string &password) const {
  // Hash the password then check it against the password_hash
  return password == password_hash;
}
