#pragma once
#include "memory_model.h"

struct memory
{
	byte_t stack_ptr;
	byte_t heap_ptr;
	byte_t static_ptr;
	byte_t execute_ptr;
	heap mem;
	stack _stack;
	registers<words::BYTE> registers_list;


	memory(byte_t stack_size, byte_t heap_size,
		byte_t static_size, byte_t execute_size);


	byte_t* operator[](byte_t ptr);

};