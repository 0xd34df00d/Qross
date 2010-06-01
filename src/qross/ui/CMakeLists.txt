include_directories(${CMAKE_SOURCE_DIR}/..)

FIND_PACKAGE (Qt4 REQUIRED)
SET (QT_USE_QTSCRIPT TRUE)
SET (QT_USE_QTXML TRUE)
INCLUDE (${QT_USE_FILE})

set(qrossui_LIB_SRCS
   model.cpp
   )
   
set(qrossui_LIB_HEADERS
	model.h
	)
	
QT4_WRAP_CPP (qrossui_LIB_MOC_SRCS ${qrossui_LIB_HEADERS})

add_library(qrossui SHARED ${qrossui_LIB_SRCS} ${qrossui_LIB_MOC_SRCS})
target_link_libraries(qrossui qrosscore ${QT_LIBRARIES})

# TODO: DESTINATION
install(TARGETS qrossui DESTINATION lib)

########### install files ###############

#install(FILES guiclient.h model.h view.h DESTINATION ${INCLUDE_INSTALL_DIR}/qross/ui)
install(FILES model.h DESTINATION include/qross/ui COMPONENT Devel)
