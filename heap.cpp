#include "heap.h"
#include <memory>

heap::heap(byte_t size) :write_ptr(0), heap_size(size)
{
	begin_ptr = (byte_t*)malloc(size);

}

byte_t heap::allocate(byte_t size)
{
	byte_t res_ptr = write_ptr;
	write_ptr += size;
	if (write_ptr > heap_size) {
		write_ptr -= size;
		throw std::exception("Heap overflow");
	}
	return res_ptr;
}

void heap::free(byte_t)
{
	
}
