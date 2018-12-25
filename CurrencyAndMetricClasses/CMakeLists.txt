cmake_minimum_required(VERSION 3.11)
project(CurrencyAndMetricClasses)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/Currency.cpp
    src/Source.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ./include/)