
cmake_minimum_required(VERSION 3.10)
project(SecureFileAccess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library
add_library(SecureFileAccess
    src/SecureFileAccess.cpp
)

target_include_directories(SecureFileAccess
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Executable
add_executable(secure_file_access
    src/main.cpp
)

target_link_libraries(secure_file_access
    SecureFileAccess
)

# Install
install(TARGETS secure_file_access
    DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
