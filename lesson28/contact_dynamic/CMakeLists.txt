add_executable(contact_dynamic main.c contact.c)
target_include_directories(contact_dynamic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})