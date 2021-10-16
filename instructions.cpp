#include "instructions.h"
#include "memory_model.h"

#include <iostream>

namespace executors {
	// move: mov dst src -> mooving data from src to dst
	// dst could be register or memory ptr
	// src could be register or memory ptr

	void null_exec(instruction cmd, memory& mem) {

	}

	void move(register_name dst, register_name src, registers<words::WORD>& register_list);
	void move(register_name dst, byte_t* src, registers<words::WORD>& register_list);
	void move(byte_t* dst, register_name src, registers<words::WORD>& register_list);

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

	// add: add left right -> adding right to the left
	// left could be register
	// right could be register or memory ptr

	void add(register_name left, register_name right, registers<words::WORD>& register_list);
	void add(register_name left, byte_t* right, registers<words::WORD>& register_list);

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

	void add(register_name left, register_name right, registers<words::WORD>& register_list) {
		register_list[left] = register_list[left] + register_list[right];
	}

	void add(register_name left, byte_t* right, registers<words::WORD>& register_list) {
		register_list[left] = register_list[left] + (*right);
	}

	// sub: sub left right -> subtracting right from the left
	// left could be register
	// right could be register or memory ptr

	void sub(register_name left, register_name right, registers<words::WORD>& register_list);
	void sub(register_name left, byte_t* right, registers<words::WORD>& register_list);

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

	// push: push src -> pushing src on stack
	// src could be register

	void push(register_name src, memory& mem);

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

	// pop: pop dst -> popping from stack to dst
	// dst could be register

	void pop(register_name dst, memory& mem);

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

	// cmp: cmp left right -> compearing left and right; result in FL register
	// left could be register or memory ptr
	// right could be register or memory ptr

	void cmp(register_name left, register_name right, registers<words::WORD>& register_list);
	void cmp(register_name left, byte_t* right, registers<words::WORD>& register_list);
	void cmp(byte_t* left, register_name right, registers<words::WORD>& register_list);

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

	// jmp: jmp label -> jumping to label
	// label could be register

	void jmp(register_name dst, registers<words::WORD>& register_list);

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

	// jmpe: jmpe label -> jumping to label if equals flag raised
	// label could be register

	void jmpe(register_name dst, registers<words::WORD>& register_list);

	void jmpe(instruction cmd, memory& mem) {
		bool is_left_ptr = cmd.flags & 2;
		bool is_right_ptr = cmd.flags & 1;
		std::cout << "Executing command jmpe: (" << (int)cmd.type << ", " << is_left_ptr << ", "
			<< is_right_ptr << ", " << (int)cmd.left << ", " << (int)cmd.right << ");" << std::endl;

		jmpe((register_name)cmd.left, mem.registers_list);

	}

	void jmpe(register_name dst , registers<words::WORD>& register_list) {
		if (register_list[register_name::FL].val && 1) {
			word_t new_ip = register_list[dst].val;
			register_list[register_name::IP].val = new_ip;
		}
	}

}


executing_shell::executing_shell():last_cmd_ptr(0), mem(1024, 4096, 1024, 1024) {
	commands_list[0] = {};
	commands_list[1] =  { 1,  &executors::move, 2};
	commands_list[2] =  { 2,  &executors::add, 2 };
	commands_list[3] =  { 3,  &executors::sub, 2 };
	commands_list[5] =  { 5,  &executors::cmp, 2 };
	commands_list[6] =  { 6,  &executors::jmp, 1 };
	commands_list[7] =  { 7,  &executors::jmpe, 1 };
	//commands_list[8] =  { 8,  &executors::jmp, 1 };
	//commands_list[9] =  { 9,  &executors::jmp, 1 };
	//commands_list[10] = { 10,  &executors::jmp, 1 };
	//commands_list[11] = { 11,  &executors::jmp, 1 };
	commands_list[12] = { 12, &executors::push, 1 };
	commands_list[13] = { 13, &executors::pop, 1 };
	commands_list[14] = { 14, &executors::null_exec, 1 };
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