cmake_minimum_required (VERSION 2.8.11)

set(TESTS_NAME ${MAIN_NAME}_tests)

project ( ${TESTS_NAME} CXX )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package( Qt5Core REQUIRED )
find_package( Qt5Concurrent REQUIRED )

FIND_PACKAGE( Boost COMPONENTS system unit_test_framework REQUIRED )

include_directories(    ../client
                        ../server
                        ../universal
                        ${Boost_INCLUDE_DIR} )

set( SOURCE
    ${SOURCE}
    main.cpp 
    server/book_test.cpp
    server/library_test.cpp
    server/user_test.cpp
    server/usermanagement_test.cpp
    server/networkconnection_test.cpp)

set( HEADERS
   ${HEADERS}
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable( ${TESTS_NAME} WIN32 ${SOURCE} ${HEADERS}  )

qt5_use_modules( ${TESTS_NAME} Core )
target_link_libraries( ${TESTS_NAME} ${MAIN_NAME}_server_library ${MAIN_NAME}_client_library ${Boost_LIBRARIES} )

enable_testing()
add_test(NAME runtests COMMAND advanced_cpp_library_tests)
