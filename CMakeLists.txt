cmake_minimum_required(VERSION 3.10)
project(multipy_demo)
include(FetchContent)

# Fetch libtorch and find torch by fetched
FetchContent_Declare(
        libtorch
        URL https://download.pytorch.org/libtorch/cu113/libtorch-cxx11-abi-shared-with-deps-1.11.0%2Bcu113.zip
        URL_HASH MD5=f7c14a977d7842d1079f3cda6d010ba0
)

FetchContent_Populate(libtorch)
#message(STATUS ${libtorch_SOURCE_DIR})
find_package(Torch PATHS ${libtorch_SOURCE_DIR} REQUIRED NO_DEFAULT_PATH)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS " -no-pie")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 8.1.1)

FetchContent_MakeAvailable(fmt)

FetchContent_Populate(multipy
        SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/multipy/runtime/
        URL https://github.com/pytorch/multipy/releases/download/nightly-runtime-ABI-is-one/multipy_runtime.tar.gz
        URL_HASH MD5=ed39c191f809468a7c25b5972c75f605
        )
add_library(multipy INTERFACE)
target_include_directories(multipy INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/_deps/)
target_link_libraries(multipy INTERFACE ${multipy_SOURCE_DIR}/lib/libtorch_deployinterpreter.so
        ${multipy_SOURCE_DIR}/lib/libtorch_deploy.a fmt)
include(${multipy_SOURCE_DIR}/utils.cmake)


add_subdirectory(torch_demo)
add_subdirectory(multipy_demo)
