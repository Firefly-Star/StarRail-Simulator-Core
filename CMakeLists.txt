cmake_minimum_required(VERSION 3.22)

project(starrail_simulator_core LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)

execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m pybind11 --includes
    OUTPUT_VARIABLE PYBIND11_INCLUDES_RAW
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

separate_arguments(PYBIND11_INCLUDES NATIVE_COMMAND "${PYBIND11_INCLUDES_RAW}")

file(GLOB_RECURSE STARRAIL_CPP_CORE_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

add_library(starrail_cpp_core MODULE ${STARRAIL_CPP_CORE_SOURCES})

target_include_directories(starrail_cpp_core
    PRIVATE
        include
        src/bindings
)

target_compile_options(starrail_cpp_core PRIVATE -fvisibility=hidden)
target_link_libraries(starrail_cpp_core PRIVATE Python3::Module)

foreach(include_arg IN LISTS PYBIND11_INCLUDES)
    target_compile_options(starrail_cpp_core PRIVATE "${include_arg}")
endforeach()

set_target_properties(starrail_cpp_core PROPERTIES
    PREFIX ""
    OUTPUT_NAME "starrail_cpp_core"
    SUFFIX ".so"
)
