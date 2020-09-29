cmake_minimum_required(VERSION 3.10)

# set the project name
project(cassagemd5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

execute_process (
        COMMAND bash IsLibCryptolibExist.bash
)

# add the executable
add_executable(main src/main.cpp)
add_executable(MultiThread src/multithread.cpp)
add_executable(Sequentielle src/sequentielle.cpp)

target_link_libraries(main ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)
target_link_libraries(MultiThread ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)
target_link_libraries(Sequentielle ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)