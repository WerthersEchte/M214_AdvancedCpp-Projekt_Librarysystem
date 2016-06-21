cmake_minimum_required (VERSION 2.8.11)

set(TESTS_NAME ${MAIN_NAME}_tests)

project ( ${TESTS_NAME} CXX )

FIND_PACKAGE( Boost COMPONENTS system unit_test_framework REQUIRED )

include_directories(    ../server
                        ${Boost_INCLUDE_DIR} )

set( SOURCE
   ${SOURCE}
   server/book_test.cpp
        server/main.cpp server/library_test.cpp)

set( HEADERS
   ${HEADERS}
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable( ${TESTS_NAME} WIN32 ${SOURCE} ${HEADERS}  )

target_link_libraries( ${TESTS_NAME} ${MAIN_NAME}_server_library ${MAIN_NAME}_client_library ${Boost_LIBRARIES} )

enable_testing()
add_test(NAME runtests COMMAND advanced_cpp_library_tests)