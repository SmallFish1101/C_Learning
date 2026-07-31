add_executable(leak_demo leak_demo.c)
add_executable(dangling_demo dangling_demo.c)
add_executable(fix_leak fix_leak.c)
add_subdirectory(safe_array)

# 无检测版本（普通编译）
add_executable(buffer_overflow buffer_overflow.c)

# ASan 版本（注意不要同时混用普通和 ASan 到同一个目标）
add_executable(buffer_overflow_asan buffer_overflow.c)
target_compile_options(buffer_overflow_asan PRIVATE -fsanitize=address -g)
target_link_options(buffer_overflow_asan PRIVATE -fsanitize=address)