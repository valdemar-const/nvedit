cmake_minimum_required(VERSION 3.12)

project(
  text_editor
  VERSION 0.1.1
  DESCRIPTION "simple text editor created with fltk")

find_package(FLTK REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(NVEdit src/main.cpp src/EditorWindow.cpp src/FileTab.cpp)
target_include_directories(
  NVEdit
  PRIVATE ${FLTK_INCLUDE_DIR}
  PRIVATE include)
target_link_libraries(NVEdit PRIVATE ${FLTK_LIBRARIES})
