add_executable(player_demo main.c player.c)

# 头文件在当前目录，一般情况下 CMake 会自动搜索，但显式添加更规范
target_include_directories(player_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})