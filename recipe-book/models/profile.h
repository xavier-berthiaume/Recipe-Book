#ifndef PROFILE_H
#define PROFILE_H

#include <list>
#include <string>

class Profile {

  std::string m_username;
  std::list<std::string> m_ownedRecipeIds;
  std::list<std::string> m_ownedIngredientIds;

public:
  Profile(const std::string &username);

  std::string getUsername() const;
  std::list<std::string> getOwnedRecipeIds() const;
  std::list<std::string> getownedIngredientIds() const;

  void setUsername(const std::string &username);
  void setOwnedRecipeIds(const std::list<std::string> &recipeIds);
  void setOwnedIngredientIds(const std::list<std::string> &ingredientIds);

  void addRecipeId(const std::string &id);
  void removeRecipeId(const std::string &id);

  void addIngredientId(const std::string &id);
  void removeIngredientId(const std::string &id);
};

#endif
