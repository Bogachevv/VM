#include "instructions.h"

namespace executors {
	void push(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command push: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;

		push((register_name)cmd.left, mem);

	}
	void push(register_name src, memory& mem) {
		word_t val = mem.registers_list[src].val;
		*(word_t*)mem[mem.registers_list[register_name::SP].val] = val;
		mem.registers_list[register_name::SP].val += sizeof(word_t);
	}

	void pop(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command pop: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;

		pop((register_name)cmd.left, mem);

	}

	void pop(register_name dst, memory& mem) {
		mem.registers_list[register_name::SP].val -= sizeof(word_t);
		word_t val = *(word_t*)mem[mem.registers_list[register_name::SP].val];
		mem.registers_list[dst].val = val;
	}
}