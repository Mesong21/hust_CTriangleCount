cmake_minimum_required(VERSION 3.16)
project(mesongcount)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 将源文件添加到一个变量中
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 创建一个可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

