#include <iostream>
#include "move.h"
using namespace std;

#define u8 uint_fast8_t


void Move::set(u8 start_, u8 end_)
{
	start = start_;
	end = end_;

	u8 dist = abs(end-start);

	if (dist == 1 || dist == 6 || dist == 7 || dist == 8)
		long_jump = false;
	else
		long_jump = true;
}


void Move::print()
{
	cout << int(start) << "," << int(end) << endl;
}