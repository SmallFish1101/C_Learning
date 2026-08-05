add_executable(contact_app main.c contact.c)
target_include_directories(contact_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})