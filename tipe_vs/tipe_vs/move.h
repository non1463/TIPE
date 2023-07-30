#pragma once

#include <iostream>


#define uint_fast8_t uint_fast8_t

class Move
{
public:
	uint_fast8_t start,end;
	bool long_jump;

	void set(uint_fast8_t start,uint_fast8_t end);
	void print();
};





