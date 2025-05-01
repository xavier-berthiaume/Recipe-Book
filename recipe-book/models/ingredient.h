#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {

  std::string name;
  std::string description;

public:
  Ingredient();
  Ingredient(const std::string &name, const std::string &description);

  std::string getName() const;
  std::string getDescription() const;

  void setName(const std::string &name);
  void setDescription(const std::string &description);
};

#endif
