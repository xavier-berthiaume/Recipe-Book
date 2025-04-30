#include "user.h"

#include <algorithm> // For std::find

const std::string &User::getUsername() const { return username; }

const std::string &User::getPasswordHash() const { return password_hash; }

const std::vector<Recipe> &User::getSharedRecipes() const {
  return shared_recipes;
}

void User::setUsername(const std::string &username) {
  this->username = username;
}

void User::setPasswordHash(const std::string &password_hash) {
  this->password_hash = password_hash;
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
  return password == password_hash;
}
