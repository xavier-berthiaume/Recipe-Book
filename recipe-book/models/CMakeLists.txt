# Gather all model source files
set(MODELS_SOURCES
    models/recipe.cpp
    models/ingredient.cpp
    models/user.cpp
    models/storable.cpp
    models/recipe_ingredient.cpp
    models/shared_recipe.cpp
    models/qt_user_wrapper.cpp
    models/qt_recipe_wrapper.cpp
    models/qt_ingredient_wrapper.cpp
    models/ingredient_factory.cpp
)

# Make sure to set headers too if they need moc processing
set(MODELS_HEADERS
    models/recipe.h
    models/ingredient.h
    models/user.h
    models/storable.h
    models/recipe_ingredient.h
    models/shared_recipe.h
    models/qt_user_wrapper.h
    models/qt_recipe_wrapper.h
    models/qt_ingredient_wrapper.h
    models/ingredient_factory.h
)

# Make variables available to parent scope
set(MODELS_SOURCES ${MODELS_SOURCES} ${MODELS_HEADERS} PARENT_SCOPE)
