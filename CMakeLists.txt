cmake_minimum_required (VERSION 2.8.11)

set(MAIN_NAME advanced_cpp_library)

project ( ${MAIN_NAME} CXX )

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(tests)

enable_testing()
add_test(NAME runtests COMMAND advanced_cpp_library_tests)
