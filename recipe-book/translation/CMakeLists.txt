# Make this variable available to parent scope
set(TRANSLATION_SOURCES recipe-book_fr_CA.ts PARENT_SCOPE)

# Create translation targets
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Optionally add the QM files to resources if you have a .qrc file
# qt_add_resources(TRANSLATION_RESOURCES translations.qrc)
# set(TRANSLATION_SOURCES ${TS_FILES} ${QM_FILES} ${TRANSLATION_RESOURCES} PARENT_SCOPE)
