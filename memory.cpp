#include "memory.h"

memory::memory(word_t stack_size, word_t heap_size, word_t static_size, word_t execute_size):
	mem(stack_size + heap_size + stack_size + execute_size), 
	_stack(stack_size, mem.begin_ptr + execute_size + stack_size + heap_size)
{
	execute_ptr = 0;
	static_ptr = execute_ptr + execute_size; 
	heap_ptr = static_ptr + static_size;
	stack_ptr = heap_ptr + heap_size;
	mem.write_ptr = heap_ptr;
	registers_list[register_name::IP] = execute_ptr;
	registers_list[register_name::SP] = stack_ptr;
}

byte_t* memory::operator[](word_t ptr)
{
	return (mem.begin_ptr + ptr);
}
