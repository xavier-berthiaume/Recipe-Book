#include "utils/uuid.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("UUID", "[utils][uuid]") {
  SECTION("String length") { REQUIRE(Uuid::generate().length() == 36); }

  SECTION("Version bits set") { REQUIRE(Uuid::generate()[14] == '4'); }

  SECTION("Variant bits set") {
    std::string uuid = Uuid::generate();
    char c = uuid[19];
    REQUIRE((c == '8' || c == '9' || c == 'a' || c == 'b'));
  }

  // To make sure that only the length of the string can cause failure, chars 14
  // and 19 were manually set to be RFC 9562 compliant
  SECTION("Length validation failure") {
    REQUIRE_FALSE(Uuid::isValid(
        "aaaaaaaaaaaaaa4aaaa8aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
  }

  SECTION("Version validation failure") {
    REQUIRE_FALSE(Uuid::isValid("e6c0b5c2-7a75-Zb02-ab5e-aef4ca9fa1dc"));
  }

  SECTION("Variant validation failure") {
    REQUIRE_FALSE(Uuid::isValid("e6c0b5c2-7a75-4b02-Zb5e-aef4ca9fa1dc"));
  }

  SECTION("Generated Uuids are valid") {
    REQUIRE(Uuid::isValid(Uuid::generate()));
  }
}
