#include "VM.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	stack s(1024);
	int a = 32;
	int b = -1;
	char a_ch = 'a';
	char b_ch = 1;
	s.push((byte_t*)&a, sizeof(a));
	s.push((byte_t*)&a_ch, 1);
	s.pop((byte_t*)&b_ch, 1);
	s.pop((byte_t*)&b, sizeof(b));

	cout << "b=" << b << endl;
	cout << "b_ch=" << b_ch << endl;

	registers<words::BYTE> regs;
	regs[register_name::A] = 9;

	cout << "Data in A: " << (int)regs[register_name::A].val << endl;

	executing_shell shell;
	shell.mem.registers_list[register_name::A] = 2;
	shell.mem.registers_list[register_name::B] = 2;
	shell.mem.registers_list[register_name::C] = 3;
	shell.mem.registers_list[register_name::D] = 2;
	*shell.mem[shell.mem.static_ptr] = 13;
	*shell.mem[shell.mem.static_ptr + 2] = 0;
	*shell.mem[shell.mem.static_ptr + 4] = 2;
	shell.push_cmd({ instructions::MOV, false*2 + true, 0, shell.mem.static_ptr });
	shell.push_cmd({ instructions::MOV, false * 2 + true, 8, (word_t)(shell.mem.static_ptr + word_t(2)) });

	shell.push_cmd({ instructions::ADD, false*2 + false,0, 1 });
	shell.push_cmd({ instructions::PUSH, false * 2 + false,0, 0 });
	shell.push_cmd({ instructions::POP, false * 2 + false,3, 0 });
	shell.push_cmd({ instructions::CMP, false * 2 + true,1, (word_t)(shell.mem.static_ptr + word_t(4)) });
	shell.push_cmd({ instructions::JMPE, false * 2 + false,2, 3 });
	shell.push_cmd({ instructions::NUL, false * 2 + false,0, 3 });
	
	shell.exec_next();
	shell.exec_next();
	
	shell.exec_next();
	shell.exec_next();
	shell.exec_next();
	shell.exec_next();
	shell.exec_next();

	shell.exec_next();
	shell.exec_next();
	shell.exec_next();
	shell.exec_next();
	shell.exec_next();

	shell.exec_next();


	cout << "Result: " << (int)shell.mem.registers_list[register_name::D].val << endl;
	cout << "Equals: " << (shell.mem.registers_list[register_name::FL].val & 1) << endl;
	cout << "Less then: " << (shell.mem.registers_list[register_name::FL].val & 2) << endl;
	cout << "Greater then: " << (shell.mem.registers_list[register_name::FL].val & 4) << endl;
	word_t stack_last;

	return 0;
}
