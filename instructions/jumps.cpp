#include "instructions.h"

namespace executors {
	void jmp(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command jmp: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;

		jmp((register_name)cmd.left, mem.registers_list);

	}

	void jmp(register_name dst, registers<words::WORD>& register_list) {
		register_list[register_name::IP].val = register_list[dst].val;
	}

	void jmpe(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command jmpe: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;

		jmpe((register_name)cmd.left, mem.registers_list);

	}

	void jmpe(register_name dst, registers<words::WORD>& register_list) {
		if (register_list[register_name::FL].val && 1) {
			word_t new_ip = register_list[dst].val;
			register_list[register_name::IP].val = new_ip;
		}
	}
}