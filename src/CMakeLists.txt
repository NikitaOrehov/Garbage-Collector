include_directories(../include)

project(scr)

add_library(vector STATIC Vector.cpp)

add_executable(main main.cpp Vector.cpp)