# Gather all UI source files
set(UI_SOURCES
    ui/mainwindow.cpp
    ui/recipe_form.cpp
)

set(UI_HEADERS
    ui/mainwindow.h
    ui/recipe_form.h
)

set(UI_FORMS
    ui/mainwindow.ui
)

# set(UI_RESOURCES
#     ui/resources.qrc
# )

# Make variables available to parent scope
set(UI_SOURCES ${UI_SOURCES} ${UI_HEADERS} ${UI_FORMS} PARENT_SCOPE)
# If using resources:
# set(UI_SOURCES ${UI_SOURCES} ${UI_HEADERS} ${UI_FORMS} ${UI_RESOURCES} PARENT_SCOPE)
