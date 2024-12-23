cmake_minimum_required(VERSION 3.22.1)

# Название проекта
project(Project)

# Устанавливаем стандарт языка
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включаем thread санитайзер
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g -fno-omit-frame-pointer")

# Указываем исходные файлы проекта
set(SOURCES main.cpp utils.cpp)
add_executable(Project ${SOURCES})

# Включаем использование thread санитайзера при сборке
target_compile_options(Project PUBLIC -fsanitize=thread -fno-omit-frame-pointer)
target_link_libraries(Project PUBLIC -fsanitize=thread)

# Включаем генерацию compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Включаем Clang-Tidy
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")