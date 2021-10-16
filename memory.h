#pragma once
#include "memory_model.h"

struct memory
{
	word_t stack_ptr;
	word_t heap_ptr;
	word_t static_ptr;
	word_t execute_ptr;
	heap mem;
	stack _stack;
	registers<words::WORD> registers_list;


	memory(word_t stack_size, word_t heap_size,
		word_t static_size, word_t execute_size);


	byte_t* operator[](word_t ptr);

};