#include "profile.h"

Profile::Profile(const std::string &username) : m_username(username) {}

std::string Profile::getUsername() const { return m_username; }

std::list<std::string> Profile::getownedIngredientIds() const {
  return m_ownedIngredientIds;
}

std::list<std::string> Profile::getOwnedRecipeIds() const {
  return m_ownedRecipeIds;
}

void Profile::setUsername(const std::string &username) {
  m_username = username;
}

void Profile::setOwnedIngredientIds(
    const std::list<std::string> &ingredientIds) {
  m_ownedIngredientIds = ingredientIds;
}

void Profile::setOwnedRecipeIds(const std::list<std::string> &recipeIds) {
  m_ownedRecipeIds = recipeIds;
}

void Profile::addRecipeId(const std::string &id) {
  // Check if it's already in the list
  for (const std::string &ex_id : m_ownedRecipeIds) {
    if (ex_id == id) {
      return;
    }
  }

  m_ownedRecipeIds.push_back(id);
}

void Profile::removeRecipeId(const std::string &id) {
  for (const std::string &ex_id : m_ownedRecipeIds) {
    if (ex_id == id) {
      m_ownedRecipeIds.remove(id);
      return;
    }
  }
}

void Profile::addIngredientId(const std::string &id) {
  for (const std::string &ex_id : m_ownedIngredientIds) {
    if (ex_id == id) {
      return;
    }
  }

  m_ownedIngredientIds.push_back(id);
}

void Profile::removeIngredientId(const std::string &id) {
  for (const std::string &ex_id : m_ownedIngredientIds) {
    if (ex_id == id) {
      m_ownedIngredientIds.remove(id);
      return;
    }
  }
}
