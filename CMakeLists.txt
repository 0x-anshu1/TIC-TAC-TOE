cmake_minimum_required(VERSION 3.10)
project(tic_tac_toe_sockets VERSION 0.1 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
endif()

# Compiler warnings (helpful)
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Sources
set(SOURCES game_fun.cpp)

# Server executable
add_executable(server server.cpp ${SOURCES})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Client executable
add_executable(client client.cpp ${SOURCES})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Install targets (optional)
install(TARGETS server client
        RUNTIME DESTINATION bin)

# Optional: enable testing hook if you add tests later
enable_testing()
