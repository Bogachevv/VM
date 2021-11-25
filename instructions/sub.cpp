#include "instructions.h"

namespace executors {
	void sub(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command sub: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;
		if (is_right_ptr) {

		}
		else {
			sub((register_name)cmd.left, (register_name)cmd.right, mem.registers_list);
		}
	}

	void sub(register_name left, register_name right, registers<words::WORD>& register_list) {
		register_list[left] = register_list[left] - register_list[right];
	}

	void sub(register_name left, byte_t* right, registers<words::WORD>& register_list) {
		register_list[left] = register_list[left] - (*right);
	}
}