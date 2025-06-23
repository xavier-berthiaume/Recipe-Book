#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>

#include "ingredient.h"

class Recipe : public Ingredient
{
    std::vector<std::string> m_instructions;
    std::vector<std::string> m_equipment;

    std::string m_notes;

    uint32_t m_prepTime;

public:
    Recipe();

    Recipe(const std::string &name,
           const std::string &description,
           const std::vector<std::string> &instructions,
           const std::vector<std::string> &equipment,
           const std::string &notes,
           uint32_t prep);

    std::vector<std::string> getInstructions() const;
    std::vector<std::string> getEquipment() const;
    std::string getNotes() const;
    uint32_t getPrepTime() const;

    void setInstructions(const std::vector<std::string> &instructions);
    void addInstruction(const std::string &instruction);
    void removeInstruction(const std::string &instruction);
    void removeInstruction(int index);
    void setEquipment(const std::vector<std::string> &equipment);
    void addEquipment(const std::string &equipment);
    void removeEquipment(const std::string &equipment);
    void removeEquipment(int index);
    void setNotes(const std::string &note);
    void setPrepTime(uint32_t prepTime);

};

#endif // RECIPE_H
