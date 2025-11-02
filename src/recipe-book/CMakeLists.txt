cmake_minimum_required(VERSION 3.16)

project(recipe-book VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_program(CLANG_FORMAT "clang-format")
find_program(CLANG_TIDY "clang-tidy")

set(PROJECT_SOURCES
        main.cpp

        ui/mainwindow/mainwindow.cpp
        ui/mainwindow/mainwindow.h
        ui/mainwindow/mainwindow.ui
)

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


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(recipe-book
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET recipe-book APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(recipe-book SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(recipe-book
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(recipe-book PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.recipe-book)
endif()
set_target_properties(recipe-book PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS recipe-book
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(recipe-book)
endif()
