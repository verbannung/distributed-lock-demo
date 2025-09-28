cmake_minimum_required(VERSION 3.16)
project(distributed_lock_demo)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party/googletest)
add_subdirectory(third_party/spdlog)
add_subdirectory(tests)

enable_testing()

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS src/core/*.cpp)
file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS src/server/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/**/*.h)
file(GLOB_RECURSE PROTOCOL CONFIGURE_DEPENDS src/protocol/*.cpp)
file(GLOB_RECURSE GLOBAL CONFIGURE_DEPENDS src/global/*.cpp)

add_library(distributed_lock_lib
        ${CORE_SOURCES}
        ${SERVER_SOURCES}
        ${HEADERS}
        ${PROTOCOL}
        ${GLOBAL}
)
target_include_directories(distributed_lock_lib PUBLIC src)


add_executable(distributed_lock_demo src/main.cpp)
target_link_libraries(distributed_lock_demo PRIVATE distributed_lock_lib)

