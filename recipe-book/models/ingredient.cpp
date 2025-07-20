#include "ingredient.h"

Ingredient::Ingredient(const std::string &creatorId, const std::string &name,
                       const std::string &description)
    : m_createdById(creatorId), m_name(name), m_description(description) {}

std::string Ingredient::getName() const { return m_name; }

std::string Ingredient::getDescription() const { return m_description; }

std::string Ingredient::getCreatorId() const { return m_createdById; }

void Ingredient::setName(const std::string &name) { m_name = name; }

void Ingredient::setDescription(const std::string &description) {
  m_description = description;
}
