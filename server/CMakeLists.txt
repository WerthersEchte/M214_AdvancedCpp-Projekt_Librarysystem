cmake_minimum_required (VERSION 2.8.11)

set(MAIN_NAME ${MAIN_NAME}_server)

project ( ${MAIN_NAME} CXX )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Concurrent REQUIRED )

FIND_PACKAGE( Boost COMPONENTS system regex context coroutine REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ../universal )

set( SOURCE
   ${SOURCE}
   core/book.cpp
   core/library.cpp
   core/networkconnection.cpp
   core/networkmanagement.cpp
   core/user.cpp
   core/usermanagement.cpp
   gui/librarymaingui.cpp
   gui/add+editbook.cpp
   gui/libraryviewmodel.cpp
   gui/userviewmodel.cpp
)

set( HEADERS
   ${HEADERS}
   ../universal/definitions.h
   core/book.h
   core/library.h
   core/networkconnection.h
   core/networkmanagement.h
   core/user.h
   core/usermanagement.h
   gui/librarymaingui.h
   gui/add+editbook.h
   gui/libraryviewmodel.h
   gui/userviewmodel.h
)

set( UI_FILES
   ${UI_FILES}
   gui/librarymaingui.ui
   gui/add+editbook.ui
)

QT5_WRAP_UI( UI_HEADERS
   ${UI_FILES}
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_library (${MAIN_NAME}_library ${SOURCE} ${HEADERS} ${UI_HEADERS} ${UI_FILES} )
add_executable( ${MAIN_NAME} WIN32 main.cpp )

qt5_use_modules( ${MAIN_NAME}_library Widgets Core Gui )
target_link_libraries( ${MAIN_NAME}_library ${Boost_LIBRARIES} )
target_link_libraries( ${MAIN_NAME} ${MAIN_NAME}_library )
