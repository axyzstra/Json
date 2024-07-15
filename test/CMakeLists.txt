cmake_minimum_required(VERSION 3.5)
project(test)

aux_source_directory(./ SRC)

include_directories(${HEADPATH})
# 动态库位置
link_directories(${LIBPATH})

# 设置可执行文件输出位置
set(EXECUTABLE_OUTPUT_PATH ${EXEPATH})

add_executable(${APPNAME} ${SRC})

# 将动态库链接到可执行程序
target_link_libraries(${APPNAME} ${JSONLIB})
