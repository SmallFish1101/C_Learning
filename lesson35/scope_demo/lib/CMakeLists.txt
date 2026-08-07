#  lesson35/scope_demo/lib/CMakeLists.txt
#  子目录：测试变量作用域

message(STATUS "  [Inside lib/CMakeLists.txt]")

# ---------- 实验 2 ----------
# 检查能否看到父目录的变量
message(STATUS "    TOP_VAR = ${TOP_VAR}")   # 预期：top_level_value（可以看到父目录变量）

# ---------- 实验 1 的变量设置 ----------
# 在子目录中新建一个变量（默认只影响本目录及更深子目录）
set(MY_VAR        "lib_value")
set(CHILD_VAR     "child_value")

# ---------- 实验 3 ----------
# 使用 PARENT_SCOPE 将变量传递到父目录
set(PARENT_PASSED "passed_to_parent" PARENT_SCOPE)

message(STATUS "    After setting in lib/:")
message(STATUS "      MY_VAR        = ${MY_VAR}")        # 预期：lib_value
message(STATUS "      CHILD_VAR     = ${CHILD_VAR}")     # 预期：child_value
message(STATUS "      PARENT_PASSED = ${PARENT_PASSED}") # 预期：passed_to_parents