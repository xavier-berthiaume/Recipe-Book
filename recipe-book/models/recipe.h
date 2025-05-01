#ifndef RECIPE_H
#define RECIPE_H

#include "ingredient.h"

#include <cstdint>
#include <string>
#include <vector>

class Recipe : public Ingredient {
  std::vector<std::string> instructions;
  std::vector<std::string> equipment;
  std::string notes;
  uint32_t prep_time;
  bool is_shared;
  uint32_t like_count;

public:
  Recipe();
  Recipe(const std::string &name, const std::string &description);
  Recipe(const std::string &name, const std::string &description,
         const std::vector<std::string> &instructions,
         const std::vector<std::string> &equipment, const std::string &notes,
         uint32_t prep_time, bool is_shared, uint32_t like_count);

  const std::vector<std::string> &getInstructions() const;
  const std::vector<std::string> &getEquipment() const;
  const std::string &getNotes() const;
  uint32_t getPrepTime() const;
  bool getIsShared() const;
  uint32_t getLikeCount() const;

  void addInstruction(const std::string &instruction);
  void removeInstruction(const std::string &instruction);
  void removeInstruction(int instruction);
  void addEquipment(const std::string &equipment);
  void removeEquipment(const std::string &equipment);
  void removeEquipment(int equipment);
  void setPrepTime(uint32_t prep_time);
  void setNote(const std::string &note);
  void setIsShared(bool isShared);
  void toggleShared();
  void setLikeCount(uint32_t like_count);

  bool operator==(const Recipe &other) const;
  bool operator!=(const Recipe &other) const;
};

#endif
