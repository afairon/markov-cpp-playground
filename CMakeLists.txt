cmake_minimum_required(VERSION 3.0.0)
project(markovplay VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Boost REQUIRED system)

set(SERVER_SRC
    src/main.cpp
)

add_executable(markovplay ${SERVER_SRC})
target_link_libraries(markovplay cpprest boost_system pthread crypto)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
