cmake_minimum_required(VERSION 3.7)

# Declare projct
project(SoftbodySim)

# Install SFML lib
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_NAME "SoftbodySim")

# Building projct
file(GLOB src_files "src/*.cpp" "include/*.h")
add_executable(SoftbodySim ${src_files})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -g  -ffast-math  ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g ")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -g ")

# Linking libraries
find_package(SFML 2 REQUIRED system window graphics)

if(SFML_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system)
endif()