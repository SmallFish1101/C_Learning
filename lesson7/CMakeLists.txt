add_executable(const_demo const_demo.c)
add_executable(define_demo define_demo.c)
add_executable(enum_demo enum_demo.c)
add_executable(compare compare.c)
add_executable(state_machine state_machine.c)

# 显式要求 C11（VLA 在 C11 中是可选特性，但 MinGW GCC 支持）
target_compile_features(compare PRIVATE c_std_11)
target_compile_features(state_machine PRIVATE c_std_11)

# 或者也可以用 set_property：
# set_property(TARGET compare PROPERTY C_STANDARD 11)
# set_property(TARGET compare PROPERTY C_STANDARD_REQUIRED ON)