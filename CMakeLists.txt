cmake_minimum_required(VERSION 3.18.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++17")
  set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++17")
elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++1z")
  set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++1z")
endif()

project(lit)

set(SOURCE_EXE Main.cpp )		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB Lit.h Exception.h FileWatcher.h)			# Тоже самое, но для библиотеки

add_library(lib STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

add_executable(lit ${SOURCE_EXE})	# Создает исполняемый файл с именем main

#target_compile_features(Main PRIVATE cxx_std_17)

set_target_properties(lib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(lit lib stdc++fs )		# Линковка программы с библиотекой

#set_target_properties(hello PROPERTIES LINKER_LANGUAGE CXX)