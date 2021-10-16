#pragma once
#include "word_types.h"

struct stack
{
	byte_t* end_ptr;
	byte_t* stack_pointer;
	size_t stack_size;

	stack(size_t size);

	stack(size_t size, byte_t* begin_pointer);

	void push(byte_t* ptr, size_t size);

	void pop(byte_t* ptr, size_t size);

};