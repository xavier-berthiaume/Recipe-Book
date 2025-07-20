#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
  std::string m_name;
  std::string m_description;
  const std::string m_createdById;

public:
  Ingredient(const std::string &creatorId, const std::string &name = "",
             const std::string &description = "");

  std::string getName() const;
  std::string getDescription() const;
  std::string getCreatorId() const;

  void setName(const std::string &name);
  void setDescription(const std::string &description);
};

#endif
