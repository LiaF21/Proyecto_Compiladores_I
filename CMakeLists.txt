cmake_minimum_required(VERSION 3.10)

project(Proyecto_Compiladores_I VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SOURCES
  Main.cpp
  Lexer.cpp
)

add_executable(lexer ${SOURCES})

