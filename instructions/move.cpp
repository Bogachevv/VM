#include "instructions.h"


namespace executors {

	void move(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command move: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;
		if (is_left_ptr) {
			move(mem.mem.begin_ptr + cmd.left, (register_name)cmd.right, mem.registers_list);
		}
		else if (is_right_ptr) {
			move((register_name)cmd.left, mem.mem.begin_ptr + cmd.right, mem.registers_list);
		}
		else {
			move((register_name)cmd.left, (register_name)cmd.right, mem.registers_list);
		}
	}

	void move(register_name dst, register_name src, registers<words::WORD>& register_list) {
		register_list[dst] = register_list[src];
	}

	void move(register_name dst, byte_t* src, registers<words::WORD>& register_list) {
		register_list[dst] = *src;
	}

	void move(byte_t* dst, register_name src, registers<words::WORD>& register_list) {
		*dst = register_list[src].val;
	}
}