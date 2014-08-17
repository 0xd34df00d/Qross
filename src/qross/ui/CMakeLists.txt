include_directories(${CMAKE_SOURCE_DIR}/..)

if (USE_QT5)
	find_package (Qt5Core REQUIRED)
else ()
	find_package (Qt4 REQUIRED)
	set (QT_USE_QTSCRIPT TRUE)
	set (QT_USE_QTXML TRUE)
	include (${QT_USE_FILE})
endif ()

set(qrossui_LIB_SRCS
   model.cpp
   )
   
set(qrossui_LIB_HEADERS
	model.h
	)
	
if (USE_QT5)
	QT5_WRAP_CPP (qrossui_LIB_MOC_SRCS ${qrossui_LIB_HEADERS})
else ()
	QT4_WRAP_CPP (qrossui_LIB_MOC_SRCS ${qrossui_LIB_HEADERS})
endif ()

add_library(qrossui SHARED ${qrossui_LIB_SRCS} ${qrossui_LIB_MOC_SRCS})
target_link_libraries(qrossui qrosscore ${QT_LIBRARIES})
set_property(TARGET qrossui PROPERTY VERSION "0.1")

# TODO: DESTINATION
install(TARGETS qrossui DESTINATION lib${LIB_SUFFIX})

if (USE_QT5)
	QT5_USE_MODULES (qrossui Script Widgets)
endif ()

########### install files ###############

#install(FILES guiclient.h model.h view.h DESTINATION ${INCLUDE_INSTALL_DIR}/qross/ui)
install(FILES model.h DESTINATION include/qross/ui COMPONENT Devel)
