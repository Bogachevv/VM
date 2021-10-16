#pragma once
#include "word_types.h"

constexpr auto registers_count = 9;
enum register_name {
	A = 0,
	B = 1,
	C = 2,
	D = 3,
	SP = 5,
	IP = 6,
	BP = 7,
	FL = 8,
};

template<words>
struct word_type_check {
	//void result;
};

template<>
struct word_type_check<words::BYTE> {
	byte_t result;
};

template<>
struct word_type_check<words::WORD> {
	word_t result;
};

template<>
struct word_type_check<words::DWORD> {
	dword_t result;
};

template<>
struct word_type_check<words::QWORD> {
	qword_t result;
};

template <words word_type>
struct register_val
{
	typedef decltype(word_type_check<word_type>::result) val_t;
	val_t val;

	void operator=(val_t value) {
		this->val = value;
	}

	val_t friend operator+(register_val left, val_t right) {
		return left.val + right;
	}

	val_t friend operator+(register_val left, register_val right) {
		return left.val + right.val;
	}

	val_t friend operator-(register_val left, val_t right) {
		return left.val - right;
	}

	val_t friend operator-(register_val left, register_val right) {
		return left.val - right.val;
	}

};

//template<>
//struct register_val<words::BYTE>
//{
//	decltype(word_type_check<words::BYTE>::result) val;
//
//	void operator=(byte_t value);
//};

//byte_t operator+(register_val<words::BYTE>, byte_t);
//
//byte_t operator+(register_val<words::BYTE>, register_val<words::BYTE>);
//
//byte_t operator-(register_val<words::BYTE>, byte_t);
//
//byte_t operator-(register_val<words::BYTE>, register_val<words::BYTE>);


//template<>
//struct register_val<words::WORD>
//{
//	word_t val;
//
//	void operator=(word_t value);
//};
//
//template<>
//struct register_val<words::DWORD>
//{
//	// TODO: make compile time architecture check
//	// WARNING: this code works only with amd_x64
//
//
//
//};
//
//template<>
//struct register_val<words::QWORD>
//{
//	// TODO: make compile time architecture check
//	// WARNING: this code works only with amd_x64
//
//
//
//};

template <words w_type>
struct registers
{
	typedef register_val<w_type> reg_val;

	reg_val register_vals[registers_count];

	registers() {

	}

	reg_val get_register(register_name name) {
		if (name >= registers_count) {
			// ERROR
		}

		return this->register_vals[name];
	}

	void set_register(register_name name, reg_val value) {
		if (name >= registers_count) {
			// ERROR
		}

		this->register_vals[name] = value;

	}

	reg_val& operator[](register_name name) {
		return this->register_vals[name];
	}

};