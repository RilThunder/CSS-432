cmake_minimum_required(VERSION 3.10)
project(HW1)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW1 Server.cpp Client.cpp ClientBenchMark.cpp ServerBenchMark.cpp benchmark/LocalServerBenchMark.cpp benchmark/LocalClientBenchMark.cpp)