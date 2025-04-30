#include "recipe.h"

Recipe::Recipe() : Recipe("", "") {}

Recipe::Recipe(const std::string &name, const std::string &description)
    : Recipe(name, description, std::vector<std::string>(),
             std::vector<std::string>(), "", 0, false, 0) {}

Recipe::Recipe(const std::string &name, const std::string &description,
               const std::vector<std::string> &instructions,
               const std::vector<std::string> &equipment,
               const std::string &notes, uint32_t prep_time, bool is_shared,
               uint32_t like_count)
    : Ingredient(name, description), instructions(instructions),
      equipment(equipment), notes(notes), prep_time(prep_time),
      is_shared(is_shared), like_count(like_count) {}

const std::vector<std::string> &Recipe::getInstructions() const {
  return instructions;
}

const std::vector<std::string> &Recipe::getEquipment() const {
  return equipment;
}

const std::string &Recipe::getNotes() const { return notes; }

uint32_t Recipe::getPrepTime() const { return prep_time; }

bool Recipe::getIsShared() const { return is_shared; }

uint32_t Recipe::getLikeCount() const { return like_count; }

void Recipe::addInstruction(const std::string &instruction) {
  instructions.push_back(instruction);
}

void Recipe::removeInstruction(const std::string &instruction) {
  for (auto it = instructions.begin(); it != instructions.end();) {
    if (*it == instruction) {
      it = instructions.erase(it);
    } else {
      ++it;
    }
  }
}

void Recipe::removeInstruction(int index) {
  if (index >= 0 && index < static_cast<int>(instructions.size())) {
    instructions.erase(instructions.begin() + index);
  }
}

void Recipe::addEquipment(const std::string &equipment) {
  this->equipment.push_back(equipment);
}

void Recipe::removeEquipment(const std::string &equipment) {
  for (auto it = this->equipment.begin(); it != this->equipment.end();) {
    if (*it == equipment) {
      it = this->equipment.erase(it);
    } else {
      ++it;
    }
  }
}

void Recipe::removeEquipment(int index) {
  if (index >= 0 && index < static_cast<int>(equipment.size())) {
    equipment.erase(equipment.begin() + index);
  }
}

void Recipe::setPrepTime(uint32_t prep_time) { this->prep_time = prep_time; }

void Recipe::setNote(const std::string &note) { notes = note; }

void Recipe::toggleShared() { is_shared = !is_shared; }

void Recipe::setIsShared(bool is_shared) { this->is_shared = is_shared; }

void Recipe::setLikeCount(uint32_t like_count) {
  this->like_count = like_count;
}
