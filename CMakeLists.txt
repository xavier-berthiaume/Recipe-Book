cmake_minimum_required(VERSION 3.16)
project(recipe-book)

# Application metadata
set(APPLICATION_ID "ca.maisonberthiaume.recipe-book" CACHE STRING "Application ID (reverse domain name)")
set(APPLICATION_NAME "Recipe Book" CACHE STRING "Human-readable application name")
set(APPLICATION_VERSION "0.5.0" CACHE STRING "Application version")

# Convert to preprocessor definitions
add_compile_definitions(APPLICATION_ID="${APPLICATION_ID}")
add_compile_definitions(APPLICATION_NAME="${APPLICATION_NAME}")
add_compile_definitions(APPLICATION_VERSION="${APPLICATION_VERSION}")

# Default log level
set(DEFAULT_LOG_LEVEL "INFO" CACHE STRING "Default log level (DEBUG, INFO, WARNING, ERROR)")

# Convert to preprocessor definition
if(DEFAULT_LOG_LEVEL STREQUAL "DEBUG")
    set(LOG_LEVEL_DEFINE "G_LOG_LEVEL_DEBUG")
elseif(DEFAULT_LOG_LEVEL STREQUAL "INFO")
    set(LOG_LEVEL_DEFINE "G_LOG_LEVEL_INFO")
elseif(DEFAULT_LOG_LEVEL STREQUAL "WARNING")
    set(LOG_LEVEL_DEFINE "G_LOG_LEVEL_WARNING")
elseif(DEFAULT_LOG_LEVEL STREQUAL "ERROR")
    set(LOG_LEVEL_DEFINE "G_LOG_LEVEL_ERROR")
else()
    set(LOG_LEVEL_DEFINE "G_LOG_LEVEL_INFO")
endif()

add_compile_definitions(DEFAULT_LOG_LEVEL=${LOG_LEVEL_DEFINE})
add_compile_definitions(LOG_LEVEL_STRING="${DEFAULT_LOG_LEVEL}")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTK3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0 glibmm-2.68 giomm-2.68)

find_program(CLANG_FORMAT "clang-format")
find_program(CLANG_TIDY "clang-tidy")

add_executable(${PROJECT_NAME} 
  src/main.cpp

  src/utils/configmanager.h src/utils/configmanager.cpp
  src/utils/loggingmanager.h src/utils/loggingmanager.cpp
  src/utils/uuid.h src/utils/uuid.cpp

  src/core/storable.h
  src/core/abstractstorable.h
  src/core/abstractingredient.h
  src/core/abstractingredientdecorator.h
  src/core/ingredient.h src/core/ingredient.cpp
  src/core/recipe.h src/core/recipe.cpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Include directories and link libraries
# It is highly recommended to use the -DCMAKE_EXPORT_COMPILE_COMMANDS=1 compilation 
# flag to avoid having your IDE throwing errors about not finding the GTK or GTKmm libraries.
target_include_directories(${PROJECT_NAME} PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER})

if(CLANG_FORMAT)
    add_custom_target(format
      COMMAND ${CLANG_FORMAT} -i ${PROJECT_SOURCES}
        COMMENT "Formatting all source files with clang-format..."
    )
endif()

if(CLANG_TIDY)
    get_filename_component(PROJECT_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)
    set(CLANG_TIDY_WRAPPER "${PROJECT_ROOT}/run_clang_tidy.sh")
    
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_WRAPPER}")
endif()

# Set up unit tests
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.11.0
)
FetchContent_MakeAvailable(Catch2)

add_library(core_lib STATIC 
  src/utils/uuid.h src/utils/uuid.cpp
)

target_include_directories(core_lib 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(core_lib
  ${GLIB_LIBRARIES}  
)

add_executable(tests
  test/test_main.cpp
  
  test/utils/uuid_test.cpp
)

target_link_libraries(tests
  PRIVATE
    Catch2::Catch2WithMain
    core_lib
    ${GLIB_LIBRARIES}
)

enable_testing()

add_test(NAME AllUnitTests COMMAND tests)

add_test(NAME UtilityTests COMMAND tests [utils])
