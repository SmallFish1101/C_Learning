add_executable(skill_demo main.c skill.c)
target_include_directories(skill_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})