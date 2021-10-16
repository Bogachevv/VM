#include "stack.h"
#include <memory>

stack::stack(size_t size): stack_size(size) {
	stack_pointer = (byte_t*)malloc(stack_size);
	end_ptr = stack_pointer + stack_size;
}

stack::stack(size_t size, byte_t* begin_pointer): 
stack_size(size), stack_pointer(begin_pointer), end_ptr(begin_pointer + size)
{

}

void stack::push(byte_t* ptr, size_t size) {
	if (stack_pointer + size >= end_ptr) {
		throw std::exception("Stack overflow");
	}

	for (size_t i = 0; i < size; ++i) {
		*stack_pointer = *ptr;
		++ptr;
		++stack_pointer;
	}

}

void stack::pop(byte_t* ptr, size_t size) {
	// TODO: check stack underflow

	for (byte_t* write_ptr = ptr + size - 1; write_ptr >= ptr; --write_ptr) {
		--stack_pointer;
		*write_ptr = *stack_pointer;
	}

}