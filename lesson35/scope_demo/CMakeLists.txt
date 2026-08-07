#  lesson35/scope_demo/CMakeLists.txt
#  练习二：CMake 变量作用域实验

cmake_minimum_required(VERSION 3.10)
project(VariableScopeDemo C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ---------- 实验准备 ----------
# 在父目录设置一个变量
set(TOP_VAR "top_level_value")

message(STATUS "============================================")
message(STATUS "  CMake Variable Scope Experiment")
message(STATUS "============================================")

# ---------- 实验 1 ----------
# 在进入子目录之前，MY_VAR 还没有被设置
message(STATUS "  [Before add_subdirectory]")
message(STATUS "    MY_VAR  = ${MY_VAR}")    # 预期：空
message(STATUS "    TOP_VAR = ${TOP_VAR}")   # 预期：top_level_value

add_subdirectory(lib)

# ---------- 实验 1 的结果 ----------
# 从子目录返回后，检查 MY_VAR 是否可见
message(STATUS "  [After add_subdirectory(lib)]")
message(STATUS "    MY_VAR        = ${MY_VAR}")        # 预期：空（子目录变量不影响父目录）
message(STATUS "    CHILD_VAR     = ${CHILD_VAR}")     # 预期：空（同上）
message(STATUS "    PARENT_PASSED = ${PARENT_PASSED}") # 预期：passed_to_parent（PARENT_SCOPE 生效）
message(STATUS "    TOP_VAR       = ${TOP_VAR}")       # 预期：top_level_value（不受子目录影响）

message(STATUS "============================================")

# 额外的可执行文件——仅为了让 CMake 能正常完成配置
add_executable(scope_demo dummy.c)