#include "uuid.h"

#include <random>
#include <sstream>

std::string Uuid::generate() {
  std::random_device rd;
  std::mt19937 gen(rd());

  // Generator for a random number between 0 and 15
  std::uniform_int_distribution<> dis(0, 15);

  // Generator for a random number between 8 and 11
  std::uniform_int_distribution<> dis2(8, 11);

  std::stringstream ss;
  ss << std::hex;

  for (int i = 0; i < 8; i++) {
    ss << dis(gen);
  }
  ss << "-";

  for (int i = 0; i < 4; i++) {
    ss << dis(gen);
  }
  ss << "-4"; // Version 4 UUID

  for (int i = 0; i < 3; i++) {
    ss << dis(gen);
  }
  ss << "-";

  ss << dis2(gen); // Variant
  for (int i = 0; i < 3; i++) {
    ss << dis(gen);
  }
  ss << "-";

  for (int i = 0; i < 12; i++)
    ss << dis(gen);

  return ss.str();
}

bool Uuid::isValid(const std::string &uuid) {
  if (uuid.length() != 36)
    return false;

  for (size_t i = 0; i < uuid.length(); i++) {
    char c = uuid[i];
    if (i == 8 || i == 13 || i == 18 || i == 23) {
      if (c != '-')
        return false;
    } else if (i == 14) {
      if (c != '4') // Version 4 UUID
        return false;
    } else if (i == 19) {
      if (c != '8' && c != '9' && c != 'a' && c != 'b')
        return false;
    } else {
      if (!std::isxdigit(c))
        return false;
    }
  }

  return true;
}
