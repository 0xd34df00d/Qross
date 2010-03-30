include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/kfile
)

FIND_PACKAGE (Qt4 REQUIRED)
SET (QT_USE_QTDESIGNER TRUE)
SET (QT_USE_QTUITOOLS TRUE)
INCLUDE (${QT_USE_FILE})

############################################
# the forms module

set(krossmoduleforms_SRCS form.cpp)
# TODO: add_plugin?
#kde4_add_plugin(krossmoduleforms ${krossmoduleforms_SRCS})

#target_link_libraries(krossmoduleforms ${QT_LIBRARIES} krosscore krossui)
#install(TARGETS krossmoduleforms DESTINATION ${PLUGIN_INSTALL_DIR})

############################################
# the kdetranslation module

set(krossmodulekdetranslation_SRCS translation.cpp)
# TODO: add_plugin?
#kde4_add_plugin(krossmodulekdetranslation ${krossmodulekdetranslation_SRCS})
#target_link_libraries(krossmodulekdetranslation ${QT_LIBRARIES} krosscore)
#install(TARGETS krossmodulekdetranslation DESTINATION ${PLUGIN_INSTALL_DIR})
