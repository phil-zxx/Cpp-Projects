cmake_minimum_required(VERSION 3.11)
project(CppCodeSnippets)

set(CMAKE_CXX_STANDARD 17)

set(MY_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MY_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}_${CMAKE_HOST_SYSTEM_PROCESSOR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MY_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}_${CMAKE_HOST_SYSTEM_PROCESSOR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MY_ROOT_DIR}/build/${CMAKE_BUILD_TYPE}_${CMAKE_HOST_SYSTEM_PROCESSOR})

FILE(GLOB CMAKE_FILE_LIST */CMakeLists.txt)
message(STATUS "# Adding the following sub-projects:")

foreach(CMAKE_FILE ${CMAKE_FILE_LIST})
    get_filename_component(SUB_FOLDER ${CMAKE_FILE} PATH)
    get_filename_component(PROJ_NAME  ${SUB_FOLDER} NAME)
    add_subdirectory(${SUB_FOLDER})
    message(STATUS "#   ${PROJ_NAME}")
endforeach()
