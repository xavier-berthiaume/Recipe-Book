#include "core/ingredient.h"

#include <catch2/catch_test_macros.hpp>
#include <memory>

TEST_CASE("Ingredient", "[core][ingredient]")
{
  SECTION("Object creation")
  {
    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));

    REQUIRE(ingredient != nullptr);
  }

  SECTION("Getters")
  {
    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));

    REQUIRE(ingredient->getId() == "identifier");
    REQUIRE(ingredient->getCreatedById() == "created_by_id");
    REQUIRE(ingredient->getName() == "ingredient_name");
    REQUIRE(ingredient->getDescription() == "ingredient_description");
    REQUIRE(ingredient->getFlavor() == "ingredient_flavor_text");
  }

  SECTION("Setters")
  {
    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));

    ingredient->setName("new_identifier");
    ingredient->setDescription("new_description");
    ingredient->setFlavor("new_flavor");
    ingredient->setUpdateDate(0);

    REQUIRE(ingredient->getName() == "new_identifier");
    REQUIRE(ingredient->getDescription() == "new_description");
    REQUIRE(ingredient->getFlavor() == "new_flavor");
    REQUIRE(ingredient->getUpdateDate() == 0);
  }

  // We create a new object before every test to reset the was_modified flag
  SECTION("Modified flag")
  {
    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    ingredient->setName("new_identifier");
    REQUIRE(ingredient->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    ingredient->setDescription("new_description");
    REQUIRE(ingredient->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    ingredient->setFlavor("new_flavor");
    REQUIRE(ingredient->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    ingredient->setUpdateDate(0);
    REQUIRE(ingredient->getWasModified());
  }
}
