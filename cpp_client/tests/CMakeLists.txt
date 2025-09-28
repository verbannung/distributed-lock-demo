function(add_test_target target_name source_file)
    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name}
            PRIVATE
            distributed_lock_lib
            gtest_main
            pthread
    )
    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()

add_test_target(TestCore TestCore.cpp)
add_test_target(TestServer TestServer.cpp)