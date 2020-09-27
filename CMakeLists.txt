cmake_minimum_required(VERSION 3.10)

# set the project name
project(cassagemd5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# add the executable
add_executable(cassagemd5 src/main.cpp)


target_link_libraries(cassagemd5 ${CMAKE_SOURCE_DIR}/cryptopp/libcryptopp.a)