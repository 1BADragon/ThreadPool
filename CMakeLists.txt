cmake_minimum_required(VERSION 3.14)
project(threadpool CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build test programs" ON)

find_package(Threads)

set(THREADPOOL_SRCS
    include/threadpool/threadpool.hpp src/threadpool.cpp

    include/threadpool/entrypoint.hpp
    include/threadpool/abstractthread.hpp
    include/threadpool/thread.hpp src/thread.cpp
    include/threadpool/stdthread.hpp src/stdthread.cpp

    include/threadpool/abstractthreadfactory.hpp
    include/threadpool/threadfactory.hpp src/threadfactory.cpp
    include/threadpool/stdthreadfactory.hpp src/stdthreadfactory.cpp

    include/threadpool/jobpool.hpp src/jobpool.cpp
    include/threadpool/job.hpp src/job.cpp
    include/threadpool/worker.hpp src/worker.cpp
)

add_library(threadpool ${THREADPOOL_SRCS})
target_include_directories(threadpool PUBLIC include PRIVATE src)
target_link_libraries(threadpool Threads::Threads)
set_target_properties(threadpool
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)


if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
