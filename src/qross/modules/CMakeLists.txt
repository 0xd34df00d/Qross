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

set(qrossmoduleforms_SRCS form.cpp)
# TODO: add_plugin?
#kde4_add_plugin(qrossmoduleforms ${qrossmoduleforms_SRCS})

#target_link_libraries(qrossmoduleforms ${QT_LIBRARIES} qrosscore qrossui)
#install(TARGETS qrossmoduleforms DESTINATION ${PLUGIN_INSTALL_DIR})

############################################
# the kdetranslation module

set(qrossmodulekdetranslation_SRCS translation.cpp)
# TODO: add_plugin?
#kde4_add_plugin(qrossmodulekdetranslation ${qrossmodulekdetranslation_SRCS})
#target_link_libraries(qrossmodulekdetranslation ${QT_LIBRARIES} qrosscore)
#install(TARGETS qrossmodulekdetranslation DESTINATION ${PLUGIN_INSTALL_DIR})
