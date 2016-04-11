cmake_minimum_required (VERSION 2.8.11)

set(MAIN_NAME advanced_cpp_library)

project ( ${MAIN_NAME} CXX )

add_subdirectory(server)
add_subdirectory(client)
