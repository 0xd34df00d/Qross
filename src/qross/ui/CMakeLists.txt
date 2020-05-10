include_directories(${CMAKE_SOURCE_DIR}/..)

set(qrossui_LIB_SRCS
   model.cpp
   )

set(qrossui_LIB_HEADERS
	model.h
	)

add_library(qrossui${SHLIB_SUFFIX} SHARED ${qrossui_LIB_SRCS})
target_link_libraries(qrossui${SHLIB_SUFFIX} qrosscore${SHLIB_SUFFIX} Qt5::Script Qt5::Widgets)
set_property(TARGET qrossui${SHLIB_SUFFIX} PROPERTY VERSION "0.1")

# TODO: DESTINATION
install(TARGETS qrossui${SHLIB_SUFFIX} DESTINATION lib${LIB_SUFFIX})

########### install files ###############

#install(FILES guiclient.h model.h view.h DESTINATION ${INCLUDE_INSTALL_DIR}/qross/ui)
install(FILES model.h DESTINATION include/qross/ui COMPONENT Devel)
