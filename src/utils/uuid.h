/**
 * @file uuid.h
 * @brief Utility class that defines a construct for universally unique
 * identifier (uuid) strings.
 */
#ifndef UUID_H
#define UUID_H

#include <string>

/**
 * @brief A struct that holds necessary functions to generate and validate Uuid
 * strings.
 *
 * This struct isn't meant to be implemented as a datatype in itself since the
 * application won't need anything that robust. Instead it simply generates Uuid
 * strings and has the capacity of validating that a string is indeed a valid
 * Uuid string per its own rules.
 *
 * To be more explicit, the idea is that Uuid::generate is used to create a
 * Uuid, which should be stored as a string.
 */
struct Uuid {
  /**
   * @brief Generate a 128 bit uuid string
   *
   * The uuid string generated using this function is RFC 9562 compliant, which
   * structures a Uuid as follows:
   * - 4 random bytes for time_low
   * - 2 random bytes for time_mid
   * - 2 semi-random bytes for time_hi_and_version
   * - 1 semi-random byte for clk_seq_hi_res
   * - 1 random byte for clk_seq_low
   * - 6 random byes for node
   *
   * @return An RFC 9562 compliant string in canonical human-readable format
   */
  static std::string generate();

  /**
   * @brief Checks that the passed string is RFC 9562 compliant
   */
  static bool isValid(const std::string &);
};

#endif
