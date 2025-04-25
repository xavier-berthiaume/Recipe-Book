# Gather all model source files
set(MODELS_SOURCES
    models/recipe.cpp
    models/ingredient.cpp
)

# Make sure to set headers too if they need moc processing
set(MODELS_HEADERS
    models/recipe.h
    models/ingredient.h
)

# Make variables available to parent scope
set(MODELS_SOURCES ${MODELS_SOURCES} ${MODELS_HEADERS} PARENT_SCOPE)
