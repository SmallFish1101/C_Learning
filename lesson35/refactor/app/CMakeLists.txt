#  lesson35/refactor/app/CMakeLists.txt
#  编译主程序，链接 contact_lib 静态库

add_executable(contact_app main.c)

#  PRIVATE: main.c 需要 include "contact.h"，
#  但 contact_app 本身不会被其他目标依赖，所以用 PRIVATE 即可
target_include_directories(contact_app
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#  链接 contact_lib 静态库
#  PRIVATE: contact_app 不对外暴露 contact_lib 的接口
target_link_libraries(contact_app PRIVATE contact_lib)