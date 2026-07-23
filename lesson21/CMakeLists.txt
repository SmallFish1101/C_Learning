add_executable(debug_macro debug_macro.c)
add_executable(platform_demo platform_demo.c)
add_subdirectory(my_math_demo)
add_executable(trig_macro trig_macro.c)
# 稳定版：不定义 BETA
add_executable(version_stable version.c)

# 测试版：定义 BETA 宏
add_executable(version_beta version.c)
target_compile_definitions(version_beta PRIVATE BETA)