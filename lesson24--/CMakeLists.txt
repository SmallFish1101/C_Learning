add_executable(contact_book main.c contact.c)
target_include_directories(contact_book PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})