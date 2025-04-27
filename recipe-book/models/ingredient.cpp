#include "ingredient.h"

Ingredient::Ingredient(const std::string &name, const std::string &description)
    : name(name), description(description) {}

Ingredient::Ingredient() : Ingredient("", "") {}

std::string Ingredient::getName() const { return name; }

std::string Ingredient::getDescription() const { return description; }

void Ingredient::setName(const std::string &name) { this->name = name; }

void Ingredient::setDescription(const std::string &description) {
  this->description = description;
}
