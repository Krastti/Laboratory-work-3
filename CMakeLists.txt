cmake_minimum_required(VERSION 3.20)

project(LaboratoryWork3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(LaboratoryWork3
  main.cpp
        src/interface/solver_interface.cpp
  src/GaussSolver/lu_solver.cpp
  src/GaussSolver/matgen.cpp
  src/GaussSolver/solver.cpp
  src/complex.cpp
  src/complex_io.cpp
  src/quaternion.cpp
  src/quaternon_rotate.cpp
  src/quaternion_io.cpp
)

target_include_directories(LaboratoryWork3 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(LaboratoryWork3Tests
    tests/unit_tests.cpp
    src/GaussSolver/lu_solver.cpp
    src/GaussSolver/matgen.cpp
    src/GaussSolver/solver.cpp
    src/complex.cpp
    src/complex_io.cpp
    src/quaternion.cpp
    src/quaternon_rotate.cpp
    src/quaternion_io.cpp
)

target_include_directories(LaboratoryWork3Tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(LaboratoryWork3Example
    example.cpp
    src/GaussSolver/lu_solver.cpp
    src/GaussSolver/matgen.cpp
    src/GaussSolver/solver.cpp
    src/complex.cpp
    src/complex_io.cpp
    src/quaternion.cpp
    src/quaternon_rotate.cpp
    src/quaternion_io.cpp
)

target_include_directories(LaboratoryWork3Example PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
