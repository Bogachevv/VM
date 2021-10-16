#include "instructions.h"
#include "memory_model.h"

#include <iostream>

namespace executors {
	// move: mov dst src -> mooving data from src to dst
	// dst could be register or memory ptr
	// src could be register or memory ptr

	void move(register_name dst, register_name src, registers<words::BYTE>& register_list);
	void move(register_name dst, byte_t* src, registers<words::BYTE>& register_list);
	void move(byte_t* dst, register_name src, registers<words::BYTE>& register_list);

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

	void move(register_name dst, register_name src, registers<words::BYTE>& register_list) {
		register_list[dst] = register_list[src];
	}

	void move(register_name dst, byte_t* src, registers<words::BYTE>& register_list) {
		register_list[dst] = *src;
	}

	void move(byte_t* dst, register_name src, registers<words::BYTE>& register_list) {
		*dst = register_list[src].val;
	}

	// add: add left right -> adding right to the left
	// left could be register
	// right could be register or memory ptr

	void add(register_name left, register_name right, registers<words::BYTE>& register_list);
	void add(register_name left, byte_t* right, registers<words::BYTE>& register_list);

	void add(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command add: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;
		if (is_right_ptr) {

		}
		else {
			add((register_name)cmd.left, (register_name)cmd.right, mem.registers_list);
		}
	}

	void add(register_name left, register_name right, registers<words::BYTE>& register_list) {
		register_list[left] = register_list[left] + register_list[right];
	}

	void add(register_name left, byte_t* right, registers<words::BYTE>& register_list) {
		register_list[left] = register_list[left] + (*right);
	}

	// sub: sub left right -> subtracting right from the left
	// left could be register
	// right could be register or memory ptr

	void sub(register_name left, register_name right, registers<words::BYTE>& register_list);
	void sub(register_name left, byte_t* right, registers<words::BYTE>& register_list);

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

	void sub(register_name left, register_name right, registers<words::BYTE>& register_list) {
		register_list[left] = register_list[left] - register_list[right];
	}

	void sub(register_name left, byte_t* right, registers<words::BYTE>& register_list) {
		register_list[left] = register_list[left] - (*right);
	}

}


executing_shell::executing_shell():last_cmd_ptr(0), mem(64, 64, 64, 64) {
	commands_list[0] = {};
	commands_list[1] = { 1, &executors::move, 2};
	commands_list[2] = { 2, &executors::add, 2 };
	commands_list[3] = { 3, &executors::sub, 2 };
	programm = (instruction*)mem[0];

}

void executing_shell::push_cmd(instruction cmd) {
	programm[last_cmd_ptr] = cmd;
	++last_cmd_ptr;
}

void executing_shell::exec_next() {
	instruction cmd = programm[mem.registers_list[register_name::IP].val];
	++mem.registers_list[register_name::IP].val;
	commands_list[(size_t)cmd.type].executor(cmd, mem);
}