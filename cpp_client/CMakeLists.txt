cmake_minimum_required(VERSION 3.16) # 这里不要写 4.0，CMake 最高是 3.x
project(distributed_lock_demo)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party/googletest)

enable_testing()

file(GLOB MAIN_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB CORE_SOURCES CONFIGURE_DEPENDS "src/core/*.cpp")
file(GLOB SERVER_SOURCES CONFIGURE_DEPENDS "src/server/*.cpp")

set(SOURCES
        ${MAIN_SOURCES}
        ${CORE_SOURCES}
        ${SERVER_SOURCES}
)

include_directories(src)


add_executable(distributed_lock_demo
        src/main.cpp
        ${SOURCES})


add_executable(TestServer
        tests/TestServer.cpp
        src/core/LockManager.cpp
        src/server/TcpServer.cpp
        src/server/RequestHandler.cpp
        src/server/Protocol.cpp
)
target_link_libraries(TestServer gtest_main pthread)

add_executable(TestCore
        tests/TestCore.cpp
        src/core/LockManager.cpp
)
target_link_libraries(TestCore gtest_main pthread)

add_test(NAME TestServer COMMAND TestServer)
add_test(NAME TestCore COMMAND TestCore)