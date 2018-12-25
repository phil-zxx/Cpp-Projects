cmake_minimum_required(VERSION 3.11)
project(BlackScholesAAD)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/Source.cpp
    src/Pricer/Clock.cpp
    src/Pricer/BlackScholesPricer.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ./include/Adept2
    ./include/Pricer)