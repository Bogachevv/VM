#pragma once
#include "word_types.h"

struct heap
{
	word_t write_ptr;
	byte_t* begin_ptr;
	word_t heap_size;

	heap(word_t);

	word_t allocate(word_t size);

	void free(word_t);

};