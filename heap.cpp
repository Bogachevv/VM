#include "heap.h"
#include <memory>

heap::heap(word_t size) :write_ptr(0), heap_size(size)
{
	begin_ptr = (byte_t*)malloc(size);

}

word_t heap::allocate(word_t size)
{
	word_t res_ptr = write_ptr;
	write_ptr += size;
	if (write_ptr > heap_size) {
		write_ptr -= size;
		throw std::exception("Heap overflow");
	}
	return res_ptr;
}

void heap::free(word_t)
{
	
}
