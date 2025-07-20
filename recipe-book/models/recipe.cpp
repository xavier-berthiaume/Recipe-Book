#include "recipe.h"

Recipe::Recipe(const std::string &creatorId, const std::string &name,
               const std::string &description, const std::string &notes,
               const std::list<std::string> &ingredientIds,
               const std::list<std::string> &instructions,
               const std::list<std::string> &equipment, uint32_t prepTime)
    : Ingredient(creatorId, name, description), m_notes(notes),
      m_ingredientIds(ingredientIds), m_instructions(instructions),
      m_equipment(equipment), m_prepTime(prepTime) {}

std::list<std::string> Recipe::getIngredientIds() const {
  return m_ingredientIds;
}

std::list<std::string> Recipe::getInstructions() const {
  return m_instructions;
}

std::list<std::string> Recipe::getEquipment() const { return m_equipment; }

std::string Recipe::getNotes() const { return m_notes; }

uint32_t Recipe::getPrepTime() const { return m_prepTime; }

void Recipe::setIngredientIds(const std::list<std::string> &ingredientId) {
  m_ingredientIds = ingredientId;
}

void Recipe::addIngredientId(const std::string &ingredientId) {
  if (ingredientId.empty())
    return;

  m_ingredientIds.push_front(ingredientId);
}

void Recipe::removeIngredientId(const std::string &ingredientId) {
  if (ingredientId.empty())
    return;

  for (auto it = m_ingredientIds.begin(); it != m_ingredientIds.end();) {
    if (*it == ingredientId) {
      m_ingredientIds.erase(it);
    } else {
      it++;
    }
  }
}

void Recipe::setInstructions(const std::list<std::string> &instructions) {
  m_instructions = instructions;
}

void Recipe::addInstruction(const std::string &instruction) {
  if (instruction.empty())
    return;

  m_instructions.push_back(instruction);
}

void Recipe::removeInstruction(const std::string &instruction) {
  if (instruction.empty())
    return;

  for (auto it = m_instructions.begin(); it != m_instructions.end();) {
    if (*it == instruction) {
      m_instructions.erase(it);
    } else {
      it++;
    }
  }
}

/*
void Recipe::removeInstruction(int index) {
  if (index < 0 || index >= m_instructions.size())
    return;

  m_instructions.erase(m_instructions.begin() + index);
}
*/

void Recipe::setEquipment(const std::list<std::string> &equipment) {
  m_equipment = equipment;
}

void Recipe::addEquipment(const std::string &equipment) {
  if (equipment.empty())
    return;

  m_equipment.push_back(equipment);
}

void Recipe::removeEquipment(const std::string &equipment) {
  if (equipment.empty())
    return;

  for (auto it = m_equipment.begin(); it != m_equipment.end();) {
    if (*it == equipment) {
      m_equipment.erase(it);
    } else {
      it++;
    }
  }
}

/*
void Recipe::removeEquipment(int index) {
  if (index < 0 || index >= m_equipment.size())
    return;

  m_equipment.erase(m_equipment.begin() + index);
}
*/

void Recipe::setNotes(const std::string &note) { m_notes = note; }

void Recipe::setPrepTime(uint32_t prepTime) { m_prepTime = prepTime; }
