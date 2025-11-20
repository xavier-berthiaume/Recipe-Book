cmake_minimum_required(VERSION 3.16)
project(test-gtk-app)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTK3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0 glibmm-2.68 giomm-2.68)

add_executable(${PROJECT_NAME} 
  src/main.cpp

  src/utils/configmanager.h src/utils/configmanager.cpp
)

# Include directories and link libraries
# It is highly reccomended to use the -DCMAKE_EXPORT_COMPILE_COMMANDS=1 compilation 
# flag to avoid having your IDE throwing errors about not finding the GTK or GTKmm libraries.
target_include_directories(${PROJECT_NAME} PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER})
