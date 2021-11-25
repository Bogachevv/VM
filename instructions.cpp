#include "instructions/instructions.h"
#include "memory_model.h"

#include <iostream>

namespace executors {
	void null_exec(instruction cmd, memory& mem){}
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