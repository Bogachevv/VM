#pragma once

enum words {
	BYTE = 1,
	WORD = 2,
	DWORD = 4,
	QWORD = 8
};

typedef unsigned char byte_t;
typedef unsigned short int word_t;
typedef unsigned int dword_t;
typedef unsigned long long qword_t;