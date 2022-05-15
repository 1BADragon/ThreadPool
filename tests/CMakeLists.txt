function(create_test TEST_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_link_libraries(${TEST_NAME} threadpool)
    set_target_properties(${TEST_NAME}
        PROPERTIES
        CXX_STANDARD 17
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

create_test(turns_on turns_on.cpp)
