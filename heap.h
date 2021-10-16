#pragma once
#include "word_types.h"

struct heap
{
	byte_t write_ptr;
	byte_t* begin_ptr;
	byte_t heap_size;

	heap(byte_t);

	byte_t allocate(byte_t size);

	void free(byte_t);

};