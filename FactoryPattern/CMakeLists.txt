cmake_minimum_required(VERSION 3.13)
project(FactoryPattern)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/ProductFactory.cpp
        src/Products.cpp
        Source.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE .)

message(${PROJECT_NAME})