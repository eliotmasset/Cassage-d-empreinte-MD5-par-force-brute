cmake_minimum_required(VERSION 3.10)

# set the project name
project(cassagemd5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# add the executable
add_executable(main src/main.cpp)
add_executable(MultiThread src/MultiThread.cpp)
add_executable(Sequentielle src/Sequentielle.cpp)

target_link_libraries(main ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)
target_link_libraries(MultiThread ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)
target_link_libraries(Sequentielle ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)