#include "ingredient.h"

Ingredient::Ingredient() {}

Ingredient::Ingredient(const std::string &name, const std::string &description)
    : m_name(name)
    , m_description(description) {

}

std::string Ingredient::getName() const {
    return m_name;
}

std::string Ingredient::getDescription() const {
    return m_description;
}

void Ingredient::setName(const std::string &name) {
    m_name = name;
}

void Ingredient::setDescription(const std::string &description) {
    m_description = description;
}
