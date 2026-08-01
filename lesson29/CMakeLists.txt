add_executable(leak_demo leak_demo.c)
add_executable(dangling_demo dangling_demo.c)
add_executable(fix_leak fix_leak.c)
add_subdirectory(safe_array)

# 无检测版本（普通编译）
add_executable(buffer_overflow buffer_overflow.c)

