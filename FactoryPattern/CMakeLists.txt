cmake_minimum_required(VERSION 3.11)
project(FactoryPattern)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/ProductFactory.cpp
    src/Products.cpp
    src/Source.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE .)

message(${PROJECT_NAME})