cmake_minimum_required(VERSION 3.20)
project(Garbage-Collector)
set(CXX_STANDARD 20)

#set(SANITIZER_FLAGS "-fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")

add_subdirectory(src)
add_subdirectory(test)