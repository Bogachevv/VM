#include "instructions.h"

namespace executors {
	void cmp(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command cmp: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;

		if (is_left_ptr) {
			cmp((mem.mem.begin_ptr + cmd.left), (register_name)cmd.right, mem.registers_list);
		}
		else if (is_right_ptr) {
			cmp((register_name)cmd.left, (mem.mem.begin_ptr + cmd.right), mem.registers_list);
		}
		else {
			cmp((register_name)cmd.left, (register_name)cmd.right, mem.registers_list);
		}

	}

	void cmp(register_name left, register_name right, registers<words::WORD>& register_list) {
		word_t left_val = register_list[left].val;
		word_t right_val = register_list[right].val;
		if (left_val == right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 1;
		}
		if (left_val < right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 2;
		}
		if (left_val > right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 4;
		}
	}

	void cmp(register_name left, byte_t* right, registers<words::WORD>& register_list) {
		word_t left_val = register_list[left].val;
		word_t right_val = *right;
		if (left_val == right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 1;
		}
		if (left_val < right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 2;
		}
		if (left_val > right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 4;
		}
	}

	void cmp(byte_t* left, register_name right, registers<words::WORD>& register_list) {
		word_t left_val = *left;
		word_t right_val = register_list[right].val;
		if (left_val == right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 1;
		}
		if (left_val < right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 2;
		}
		if (left_val > right_val) {
			register_list[register_name::FL].val = register_list[register_name::FL].val | 4;
		}
	}
}