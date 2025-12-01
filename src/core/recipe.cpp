#include "recipe.h"
#include "abstractingredientdecorator.h"
#include "ingredient.h"
#include "storable.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

Recipe::Recipe(std::unique_ptr<Ingredient> ingredient)
    : Recipe(std::move(ingredient), {}, {})
{
}

Recipe::Recipe(std::unique_ptr<Ingredient> ingredient,
               std::vector<std::string> instructions,
               std::vector<std::string> ingredient_ids)
    : AbstractIngredientDecorator(std::move(ingredient)),
      m_instructions(std::move(instructions)),
      m_ingredient_ids(std::move(ingredient_ids))
{
}

auto Recipe::getInstructionsList() const -> std::vector<std::string>
{
  return m_instructions;
}

auto Recipe::getIngredientIds() const -> std::vector<std::string>
{
  return m_ingredient_ids;
}

void Recipe::addInstruction(std::string instruction_text)
{
  if (instruction_text.empty())
  {
    return;
  }

  m_instructions.push_back(std::move(instruction_text));
  modified();
}

void Recipe::addInstruction(int position, std::string instruction_text)
{
  if (instruction_text.empty())
  {
    return;
  }

  if (position < 0 || position >= m_instructions.size())
  {
    return;
  }

  m_instructions.insert(m_instructions.begin() + position,
                        std::move(instruction_text));
  modified();
}

void Recipe::removeInstruction(int position)
{
  if (position < 0 || position >= m_instructions.size())
  {
    return;
  }

  m_instructions.erase(m_instructions.begin() + position);
  modified();
}

void Recipe::addIngredient(std::string ingredient_id)
{
  if (ingredient_id.empty())
  {
    return;
  }

  m_ingredient_ids.emplace_back(std::move(ingredient_id));
  modified();
}

void Recipe::removeIngredient(const std::string &ingredient_id)
{
  if (ingredient_id.empty())
  {
    return;
  }

  int count = 0;
  for (const auto &ingredient : m_ingredient_ids)
  {
    if (ingredient_id == ingredient)
    {
      m_ingredient_ids.erase(m_ingredient_ids.begin() + count);
      modified();
    }

    count++;
  }
}

void Recipe::accept(DatabaseVisitor *visitor) {}
