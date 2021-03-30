cmake_minimum_required(VERSION 3.5)
project(Roborobo.4)
set(CMAKE_BUILD_TYPE Debug)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()
message("Type of build: " ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")

#SET(PYTHON_EXECUTABLE /...path_to_python_exec.../python)

if (DEFINED ENV{PYTHON_EXECUTABLE})
    SET(PYTHON_EXECUTABLE $ENV{PYTHON_EXECUTABLE})
    message(${PYTHON_EXECUTABLE})
else ()
    message("PYTHON_EXECUTABLE environment variable is not set")
endif ()

if (DEFINED ENV{CONDA_PREFIX})
    message("Conda env found, using " $ENV{CONDA_PREFIX})
    list(APPEND CMAKE_MODULE_PATH "$ENV{CONDA_PREFIX}/share/cmake/")
    set(pybind11_DIR "$ENV{CONDA_PREFIX}/share/cmake/pybind11")
else()
    message("No conda environment found")
endif()

find_package(pybind11 REQUIRED)

get_cmake_property(_variableNames VARIABLES)
list(SORT _variableNames)

message("Installing for ${PYTHON_EXECUTABLE}")

file(
        GLOB_RECURSE
        SOURCE_FILES
        src/*
        prj/*
)
SET(LIB_SOURCE_FILES ${SOURCE_FILES})
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*pyroborobo/.*")

include_directories(include)
include_directories(include/contrib)
include_directories(include/core)
include_directories(include/ext)
include_directories(prj)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/")
if (NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
endif()

# FindSDL2.cmake IMPORT
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(SDL2 COMPONENTS main image REQUIRED)
find_package(Boost COMPONENTS REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
endif()

message(${SDL2_LIBRARIES})


include_directories(${SDL2_INCLUDE_DIRS})


find_package(Eigen3 REQUIRED NO_MODULE)

add_executable(roborobo ${SOURCE_FILES})
target_link_libraries(roborobo PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        Eigen3::Eigen
        )


pybind11_add_module(pyroborobo ${LIB_SOURCE_FILES})
target_compile_definitions(pyroborobo PUBLIC PYROBOROBO=1)
target_link_libraries(pyroborobo PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        Eigen3::Eigen
        )
