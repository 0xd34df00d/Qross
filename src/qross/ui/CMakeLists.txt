include_directories(${CMAKE_SOURCE_DIR}/..)

find_package (Qt5Core REQUIRED)

set(qrossui_LIB_SRCS
   model.cpp
   )

set(qrossui_LIB_HEADERS
	model.h
	)

add_library(qrossui${SHLIB_SUFFIX} SHARED ${qrossui_LIB_SRCS})
target_link_libraries(qrossui${SHLIB_SUFFIX} qrosscore${SHLIB_SUFFIX} ${QT_LIBRARIES})
set_property(TARGET qrossui${SHLIB_SUFFIX} PROPERTY VERSION "0.1")

# TODO: DESTINATION
install(TARGETS qrossui${SHLIB_SUFFIX} DESTINATION lib${LIB_SUFFIX})

QT5_USE_MODULES (qrossui${SHLIB_SUFFIX} Script Widgets)

########### install files ###############

#install(FILES guiclient.h model.h view.h DESTINATION ${INCLUDE_INSTALL_DIR}/qross/ui)
install(FILES model.h DESTINATION include/qross/ui COMPONENT Devel)
