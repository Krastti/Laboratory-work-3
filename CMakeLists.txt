cmake_minimum_required(VERSION 3.20)

project(LaboratoryWork3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(LaboratoryWork3
  main.cpp
)

target_include_directories(LaboratoryWork3 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
