#  lesson35/refactor/CMakeLists.txt
#  通讯录项目（多目录分层结构）
#
#  目录职责：
#    include/ → 公开头文件（库的接口）
#    src/     → 静态库（contact_lib）
#    app/     → 可执行文件（contact_app）

cmake_minimum_required(VERSION 3.10)
project(ContactBook C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 先构建库（因为可执行文件依赖它）
add_subdirectory(src)

# 再构建可执行文件
add_subdirectory(app)