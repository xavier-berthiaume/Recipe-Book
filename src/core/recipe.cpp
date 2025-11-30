#include "recipe.h"

Recipe::Recipe(std::unique_ptr<Ingredient> ingredient)
    : Recipe(std::move(ingredient), {}) {}

Recipe::Recipe(std::unique_ptr<Ingredient> ingredient,
               std::vector<std::string> instructions)
    : AbstractIngredientDecorator(std::move(ingredient)),
      m_instructions(std::move(instructions)) {}

auto Recipe::getInstructionsList() const -> std::vector<std::string> {
  return m_instructions;
}

void Recipe::addInstruction(std::string instruction_text) {
  if (instruction_text.length() == 0) {
    return;
  }

  m_instructions.push_back(std::move(instruction_text));
}

void Recipe::addInstruction(int position, std::string instruction_text) {
  if (instruction_text.length() == 0) {
    return;
  }

  if (position < 0 || position >= m_instructions.size()) {
    return;
  }

  m_instructions.insert(m_instructions.begin() + position,
                        std::move(instruction_text));
}

void Recipe::accept(DatabaseVisitor *visitor) {}
