cmake_minimum_required(VERSION 3.16)

project(poople_solver VERSION 1.0.0 LANGUAGES CXX)

add_executable(poople_solver src/main.cpp)
target_compile_features(poople_solver PRIVATE cxx_std_17)
target_compile_definitions(poople_solver PRIVATE
    POOPLE_DICTIONARY_PATH="${CMAKE_CURRENT_SOURCE_DIR}/db/dictionary.txt"
)

if(MSVC)
    target_compile_options(poople_solver PRIVATE /W4 /permissive-)
else()
    target_compile_options(poople_solver PRIVATE -Wall -Wextra -Wpedantic)
endif()
