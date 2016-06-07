cmake_minimum_required (VERSION 2.8.11)

set(MAIN_NAME ${MAIN_NAME}_client)

project ( ${MAIN_NAME} CXX )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Concurrent REQUIRED )

FIND_PACKAGE( Boost COMPONENTS system REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} )

set( SOURCE
   ${SOURCE}
   gui/librarymaingui.cpp
   main.cpp
   core/Client.cpp
)
set( HEADERS
   ${HEADERS}
   gui/librarymaingui.h
   core/Client.h
)

set( UI_FILES
   ${UI_FILES}
   gui/ui/mainwindow.ui
)

QT5_WRAP_UI( UI_HEADERS
   ${UI_FILES}
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_library (${MAIN_NAME}_library ${SOURCE} ${HEADERS} ${UI_HEADERS} ${UI_FILES} )
add_executable( ${MAIN_NAME} WIN32 main.cpp )

qt5_use_modules( ${MAIN_NAME}_library Widgets Core Gui )
target_link_libraries( ${MAIN_NAME} ${MAIN_NAME}_library ${Boost_LIBRARIES} )
