# CMakeList.txt: проект CMake для VM; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("VM")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (VM "VM.cpp" "VM.h" "stack.h" "stack.cpp" "registers.h" "word_types.h"   "instructions/instructions.h" "instructions.cpp" "memory_model.h" "heap.h" "heap.cpp" "memory.h" "memory.cpp" "instructions/move.cpp" "instructions/add.cpp" "instructions/sub.cpp" "instructions/stack.cpp"  "instructions/cmp.cpp" "instructions/jumps.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
