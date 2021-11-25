#pragma once

#include "../memory.h"

#include "iostream"

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
	JMPGE = 10, //jump if greater equals
	JMPLE = 11, //jump if less equals
	PUSH = 12,  //push data to stack
	POP = 13,   //pop data from stack
	NUL = 14,
};

struct instruction
{
	instructions type;
	// is_left_ptr = flags & 2
	// is_right_ptr = flags & 1
	byte_t flags; 
	word_t left, right;
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

namespace executors {
	void null_exec(instruction cmd, memory& mem);

	// move: mov dst src -> mooving data from src to dst
	// dst could be register or memory ptr
	// src could be register or memory ptr
	void move(instruction cmd, memory& mem);
	void move(register_name dst, register_name src, registers<words::WORD>& register_list);
	void move(register_name dst, byte_t* src, registers<words::WORD>& register_list);
	void move(byte_t* dst, register_name src, registers<words::WORD>& register_list);

	// add: add left right -> adding right to the left
	// left could be register
	// right could be register or memory ptr
	void add(instruction cmd, memory& mem);
	void add(register_name left, register_name right, registers<words::WORD>& register_list);
	void add(register_name left, byte_t* right, registers<words::WORD>& register_list);

	// sub: sub left right -> subtracting right from the left
	// left could be register
	// right could be register or memory ptr
	void sub(instruction cmd, memory& mem);
	void sub(register_name left, register_name right, registers<words::WORD>& register_list);
	void sub(register_name left, byte_t* right, registers<words::WORD>& register_list);

	// push: push src -> pushing src on stack
	// src could be register
	void push(instruction cmd, memory& mem);
	void push(register_name src, memory& mem);


	// pop: pop dst -> popping from stack to dst
	// dst could be register
	void pop(instruction cmd, memory& mem);
	void pop(register_name dst, memory& mem);

	// cmp: cmp left right -> compearing left and right; result in FL register
	// left could be register or memory ptr
	// right could be register or memory ptr
	void cmp(instruction cmd, memory& mem);
	void cmp(register_name left, register_name right, registers<words::WORD>& register_list);
	void cmp(register_name left, byte_t* right, registers<words::WORD>& register_list);
	void cmp(byte_t* left, register_name right, registers<words::WORD>& register_list);

	// jmp: jmp label -> jumping to label
	// label could be register
	void jmp(instruction cmd, memory& mem);
	void jmp(register_name dst, registers<words::WORD>& register_list);

	// jmpe: jmpe label -> jumping to label if equals flag raised
	// label could be register
	void jmpe(instruction cmd, memory& mem);
	void jmpe(register_name dst, registers<words::WORD>& register_list);

}