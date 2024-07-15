cmake_minimum_required(VERSION 3.5)
project(json_project)

# 库生成位置
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
# 可执行文件位置
set(EXEPATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件目录
set(HEADPATH ${PROJECT_SOURCE_DIR}/include)

# 库文件名字
set(JSONLIB json)

# 可执行文件名字
set(APPNAME exe)

add_subdirectory(src)
add_subdirectory(test)