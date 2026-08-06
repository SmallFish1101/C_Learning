# 源文件列表：把两个 .c 文件都写进去
#add_executable(contact_app main.c contact.c)

# 不需要把头文件加入 add_executable——CMake 会自动扫描 #include 依赖

add_executable(contact_app_lesson34 main.c contact.c)
target_include_directories(contact_app_lesson34 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(utils_demo)
add_subdirectory(contact_file)