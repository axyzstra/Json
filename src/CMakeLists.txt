cmake_minimum_required(VERSION 3.5)
project(src)

# 查找源文件
aux_source_directory(./ SRC)
include_directories(${HEADPATH})

# 设置动态库输出位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBPATH})

# 生成动态库
add_library(${JSONLIB} SHARED ${SRC})