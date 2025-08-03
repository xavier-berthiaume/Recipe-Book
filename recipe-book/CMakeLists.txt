cmake_minimum_required(VERSION 3.16)

project(recipe-book VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

set(TS_FILES translations/recipe-book_fr_CA.ts)

set(PROJECT_SOURCES
        main.cpp
        models.h
        database.h
        database_visitor_fwd.h
        objecttypes.h

        ui/mainwindow.ui ui/mainwindow.h ui/mainwindow.cpp
        ui/abstractform.h
        ui/abstractview.h
        ui/profileform.h ui/profileform.cpp ui/profileform.ui
        ui/profileview.h ui/profileview.cpp ui/profileview.ui
        ui/genericlistmodel.h
        ui/profilelistmodel.h ui/profilelistmodel.cpp
        ui/profilelistdelegate.h ui/profilelistdelegate.cpp

        models/ingredient.h models/ingredient.cpp
        models/profile.h models/profile.cpp
        models/recipe.h models/recipe.cpp
        models/recipeingredient.h models/recipeingredient.cpp

        models/storable.h models/storable.cpp
        models/qingredient.h models/qingredient.cpp
        models/qprofile.h models/qprofile.cpp
        models/qrecipe.h models/qrecipe.cpp
        models/qrecipeingredient.h models/qrecipeingredient.cpp

        models/factorymanager.h models/factorymanager.cpp
        models/genericfactoryss.h
        models/genericfactory.h
        models/profilefactory.h models/profilefactory.cpp
        models/ingredientfactory.h models/ingredientfactory.cpp
        models/recipefactory.h models/recipefactory.cpp
        models/recipeingredientfactory.h models/recipeingredientfactory.cpp

        data/dataprovider.h data/dataprovider.cpp

        data/db/abstractdbhandler.h
        data/db/databasevisitor.h
        data/db/sqlitedbhandler.h data/db/sqlitedbhandler.cpp
        
        data/cache/abstractcache.h
        data/cache/memorycache.h data/cache/memorycache.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(recipe-book
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET recipe-book APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
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

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(recipe-book PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

target_include_directories(recipe-book PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)


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
