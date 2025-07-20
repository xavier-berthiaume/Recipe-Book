#ifndef RECIPE_H
#define RECIPE_H

#include "ingredient.h"

#include <cstdint>
#include <list>

class Recipe : public Ingredient {
  std::string m_notes;
  std::list<std::string> m_ingredientIds;
  std::list<std::string> m_instructions;
  std::list<std::string> m_equipment;
  uint32_t m_prepTime;

public:
  Recipe(const std::string &creatorId, const std::string &name,
         const std::string &description, const std::string &notes,
         const std::list<std::string> &ingredientIds,
         const std::list<std::string> &instructions,
         const std::list<std::string> &equipment, uint32_t prepTime);

  std::string getNotes() const;
  std::list<std::string> getIngredientIds() const;
  std::list<std::string> getInstructions() const;
  std::list<std::string> getEquipment() const;
  uint32_t getPrepTime() const;

  void setNotes(const std::string &notes);
  void setIngredientIds(const std::list<std::string> &ingredientIds);
  void setInstructions(const std::list<std::string> &instructions);
  void setEquipment(const std::list<std::string> &equipment);
  void setPrepTime(uint32_t prepTime);

  void addIngredientId(const std::string &ingredientId);
  void removeIngredientId(const std::string &ingredientId);

  void addInstruction(const std::string &instruction);
  void removeInstruction(const std::string &instruction);

  void addEquipment(const std::string &equipment);
  void removeEquipment(const std::string &equipment);
};

#endif
