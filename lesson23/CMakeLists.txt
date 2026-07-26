add_executable(register_macros register_macros.c)
add_executable(gpio_ctrl gpio_ctrl.c)
add_executable(bit_ops bit_ops.c)
add_executable(can_id can_id.c)

add_executable(float_inspect float_inspect.c)

# 链接数学库（某些平台需要显式指定，MinGW 通常自动链接）
target_link_libraries(float_inspect PRIVATE m)