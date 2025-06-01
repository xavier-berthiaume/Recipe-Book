# Gather all UI source files
set(UI_SOURCES
    ui/mainwindow.cpp
    ui/display_box.cpp
    ui/generic_object_display_box.cpp
    ui/ingredient_display_box.cpp
    ui/recipe_display_box.cpp
    ui/recipe_form.cpp
    ui/carousel_form.cpp
    ui/form_field.cpp
    ui/ingredient_field.cpp
    ui/recipe_carousel_form.cpp
    ui/text_field.cpp
    ui/textarea_field.cpp
    ui/textlist_field.cpp
)

set(UI_HEADERS
    ui/mainwindow.h
    ui/display_box.h
    ui/generic_object_display_box.h
    ui/ingredient_display_box.h
    ui/recipe_display_box.h
    ui/recipe_form.h
    ui/carousel_form.h
    ui/form_field.h
    ui/ingredient_field.h
    ui/recipe_carousel_form.h
    ui/text_field.h
    ui/textarea_field.h
    ui/textlist_field.h
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
