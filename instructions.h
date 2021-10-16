#pragma once

#include "memory.h"

constexpr auto instructions_count = 128;
constexpr auto max_prog_len = 1024;

enum class instructions:byte_t
{
	MOV = 1,   
	ADD = 2,  
	SUB = 3, 
	INT = 4,    //interrupt
	CMP = 5,    //compate
	JMP = 6,    //jump
	JMPE = 7,   //jump if equal
	JMPGT = 8,  //jump if greater then
	JMPLT = 9,  //jump if less then
	JMPGE = 10, //jump if reater equals
	JMPLE = 11, //jump if less equals
	PUSH = 12,  //push data to stack
	POP = 13,   //pop data from stack

};

struct instruction
{
	instructions type;
	byte_t flags; 
	// is_left_ptr = flags & 2
	// is_right_ptr = flags & 1
	byte_t left, right;
};

struct exec_ud //executor unit descriptor
{
	size_t command_id;
	void (*executor)(instruction, memory&);
	size_t args_count;
};

struct executing_shell
{
	exec_ud commands_list[instructions_count];
	memory mem;
	instruction* programm;
	//registers<words::BYTE> register_list;
	size_t last_cmd_ptr;


	executing_shell();

	void push_cmd(instruction);

	void exec_next();

};