cmake_minimum_required(VERSION 3.10)
project(RBTree VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Объявляем библиотеку типа INTERFACE, чтобы она ничего не собирала,
# но могла быть использована в качестве зависимости других целей.
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

set(HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/RBTree.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/RBTNode.h
)

set(TEMPLATES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/RBTree.inc
  ${CMAKE_CURRENT_SOURCE_DIR}/include/RBTIterator.inc
)

set(FORMAT_FILES
  ${HEADERS}
  ${TEMPLATES}
)

# Дополнительно можно добавить опции компиляции и линковки,
# которые будут применены для всех целей, использующих эту библиотеку.

target_compile_options(
  ${PROJECT_NAME}
  INTERFACE
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -fsanitize=address
)

target_link_libraries(
  ${PROJECT_NAME}
  INTERFACE
  -fsanitize=address
)

# Add cppcheck
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
  message(STATUS "cppcheck found: ${CPPCHECK}")
  list(
    APPEND CPPCHECK_ARGS
    "--enable=all"
    "--inconclusive"
    "--quiet"
    "--std=c++17"
    "--suppress=missingIncludeSystem"
    "--suppress=unusedFunction"
    "--suppress=missingInclude"
    "--suppress=unusedStructMember"
    "--suppress=variableScope"
    "--check-config"
  )
  add_custom_target(
    cppcheck
    COMMAND ${CPPCHECK} ${CPPCHECK_ARGS} ${FORMAT_FILES}
  )
else()
  message(STATUS "cppcheck not found")
endif()

# Add clang-format
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
  message(STATUS "clang-format found: ${CLANG_FORMAT}")
  list(
    APPEND CLANG_ARGS
    "-i"
    "-style=Google"
  )
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT} ${CLANG_ARGS} ${FORMAT_FILES}
  )
else()
  message(STATUS "clang-format not found")
endif()
