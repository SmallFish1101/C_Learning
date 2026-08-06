#  lesson35/refactor/src/CMakeLists.txt
#  将 contact.c 编译为静态库 libcontact_lib.a

add_library(contact_lib STATIC contact.c)

#  PUBLIC: 因为 contact.h 在 include/ 下，
#  任何链接 contact_lib 的目标（如 contact_app）也需要这个路径
#target_include_directories(contact_lib
#    PUBLIC ${CMAKE_SOURCE_DIR}/include
#)

# ★ 修复点：CMAKE_CURRENT_SOURCE_DIR 是当前 CMakeLists.txt 所在目录
#   即 lesson35/refactor/src/
#   ../include 就是 lesson35/refactor/include/
target_include_directories(contact_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)