#include "core/recipe.h"
#include "utils/uuid.h"

#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <vector>

TEST_CASE("Recipe", "[core][recipe]")
{
  SECTION("Object creation")
  {
    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));

    auto recipe =
        std::make_unique<Recipe>(Recipe(std::move(ingredient), {}, {}));

    REQUIRE(recipe != nullptr);
  }

  SECTION("Getters")
  {
    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));

    std::vector<std::string> instructions;
    instructions.emplace_back("Instruction 1");
    instructions.emplace_back("Instruction 2");
    instructions.emplace_back("Instruction 3");

    std::vector<std::string> ingredients_list;
    ingredients_list.emplace_back(Uuid::generate());
    ingredients_list.emplace_back(Uuid::generate());
    ingredients_list.emplace_back(Uuid::generate());

    auto recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));

    REQUIRE(recipe->getId() == "identifier");
    REQUIRE(recipe->getCreatedById() == "created_by_id");
    REQUIRE(recipe->getName() == "ingredient_name");
    REQUIRE(recipe->getDescription() == "ingredient_description");
    REQUIRE(recipe->getFlavor() == "ingredient_flavor_text");
    REQUIRE(recipe->getInstructionsList().size() == 3);
    REQUIRE(recipe->getIngredientIds().size() == 3);
  }

  SECTION("Setters")
  {
    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));

    std::vector<std::string> instructions;
    instructions.emplace_back("Instruction 1");
    instructions.emplace_back("Instruction 2");
    instructions.emplace_back("Instruction 3");

    std::vector<std::string> ingredients_list;
    ingredients_list.emplace_back(Uuid::generate());
    ingredients_list.emplace_back(Uuid::generate());
    ingredients_list.emplace_back(Uuid::generate());

    auto recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));

    recipe->setName("new_identifier");
    recipe->setDescription("new_description");
    recipe->setFlavor("new_flavor");
    recipe->setUpdateDate(0);
    recipe->addInstruction("Instruction 4");
    recipe->addInstruction(0, "Instruction 0");
    recipe->addIngredient(Uuid::generate());

    REQUIRE(recipe->getName() == "new_identifier");
    REQUIRE(recipe->getDescription() == "new_description");
    REQUIRE(recipe->getFlavor() == "new_flavor");
    REQUIRE(recipe->getUpdateDate() == 0);
    REQUIRE(recipe->getInstructionsList().size() == 5);
    REQUIRE(recipe->getIngredientIds().size() == 4);

    recipe->removeInstruction(0);
    recipe->removeIngredient(recipe->getIngredientIds().at(0));

    REQUIRE(recipe->getInstructionsList().size() == 4);
    REQUIRE(recipe->getIngredientIds().size() == 3);
  }

  SECTION("Modified flag")
  {
    std::vector<std::string> instructions;
    instructions.emplace_back("Instruction 1");
    instructions.emplace_back("Instruction 2");
    instructions.emplace_back("Instruction 3");

    std::vector<std::string> ingredients_list;
    ingredients_list.emplace_back(Uuid::generate());
    ingredients_list.emplace_back(Uuid::generate());
    ingredients_list.emplace_back(Uuid::generate());

    auto ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    auto recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->setName("new_name");
    REQUIRE(recipe->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->setDescription("new_description");
    REQUIRE(recipe->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->setFlavor("new_flavor");
    REQUIRE(recipe->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->addInstruction("Instruction 4");
    REQUIRE(recipe->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->addInstruction(0, "Instruction 0");
    REQUIRE(recipe->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->removeInstruction(0);
    REQUIRE(recipe->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->addIngredient(Uuid::generate());
    REQUIRE(recipe->getWasModified());

    ingredient = std::make_unique<Ingredient>(
        Ingredient("identifier", "created_by_id", "ingredient_name",
                   "ingredient_description", "ingredient_flavor_text"));
    recipe = std::make_unique<Recipe>(
        Recipe(std::move(ingredient), instructions, ingredients_list));
    recipe->removeIngredient(recipe->getIngredientIds().at(0));
    REQUIRE(recipe->getWasModified());
  }
}
