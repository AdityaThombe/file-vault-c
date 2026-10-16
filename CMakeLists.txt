cmake_minimum_required(VERSION 3.16)
project(file_vault C)

set(CMAKE_C_STANDARD 11)

add_library(vault src/vault.c)
target_include_directories(vault PUBLIC include)

enable_testing()
add_executable(test_vault tests/test_vault.c)
target_link_libraries(test_vault vault)
add_test(NAME stores_and_reads_file COMMAND test_vault roundtrip)
add_test(NAME missing_file_returns_error COMMAND test_vault missing)
add_test(NAME builds_vault_path COMMAND test_vault path)
add_test(NAME reports_file_size COMMAND test_vault size)
