#include "ingredient.h"
#include "abstractingredient.h"
#include "storable.h"
#include "utils/configmanager.h"

#include <chrono>
#include <ctime>
#include <memory>
#include <string>
#include <utility>
#include <vector>

static const int k_max_description_length_default = 999;
static const int k_max_flavor_length_default = 999;

Ingredient::Ingredient(std::string identifier, std::string created_by_id,
                       std::string name, std::string description,
                       std::string flavor)
    : Ingredient(std::move(identifier), std::move(created_by_id),
                 std::chrono::system_clock::to_time_t(
                     std::chrono::system_clock::now()),
                 std::chrono::system_clock::to_time_t(
                     std::chrono::system_clock::now()),
                 false, std::move(name), std::move(description),
                 std::move(flavor), {})
{
}

Ingredient::Ingredient(std::string identifier, std::string created_by_id,
                       time_t creation_date, time_t update_date,
                       bool was_modified, std::string name,
                       std::string description, std::string flavor,
                       std::vector<std::string> in_recipe_list)
    : AbstractIngredient(std::move(identifier), std::move(created_by_id),
                         creation_date, update_date, was_modified),
      m_name(std::move(name)), m_description(std::move(description)),
      m_flavor(std::move(flavor)), m_in_recipe_list(std::move(in_recipe_list))
{
}

void Ingredient::setName(std::string name)
{
  if (name.empty())
  {
    return;
  }

  m_name = std::move(name);
  modified();
}

auto Ingredient::getName() const -> std::string { return m_name; }

void Ingredient::setDescription(std::string description)
{
  if (description.length() >
      ConfigManager::getInstance().get("General", "MaxDescriptionLength",
                                       k_max_description_length_default))
  {
    return;
  }

  m_description = std::move(description);
  modified();
}

auto Ingredient::getDescription() const -> std::string { return m_description; }

void Ingredient::setFlavor(std::string flavor)
{
  if (flavor.length() >
      ConfigManager::getInstance().get("General", "MaxFlavorLength",
                                       k_max_flavor_length_default))
  {
    return;
  }

  m_flavor = std::move(flavor);
  modified();
}

auto Ingredient::getFlavor() const -> std::string { return m_flavor; }

auto Ingredient::getInRecipeList() const -> std::vector<std::string>
{
  return m_in_recipe_list;
}

auto Ingredient::clone() const -> std::unique_ptr<Ingredient>
{
  return std::make_unique<Ingredient>(*this);
}

void Ingredient::accept(DatabaseVisitor *visitor) {}
