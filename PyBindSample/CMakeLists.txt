cmake_minimum_required(VERSION 3.13)
project(PyBindSample)

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/python_36_win)
    target_link_libraries     (${PROJECT_NAME}                ${CMAKE_CURRENT_SOURCE_DIR}/lib/python_36_win/python36.lib)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(WARNING "No Python headers for GNU and Clang; cannot configure Python Bindings")
else()
    message(WARNING "Compiler '${CMAKE_CXX_COMPILER_ID}' is not supported for Python Bindings")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
