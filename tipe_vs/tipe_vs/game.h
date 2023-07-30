#pragma once

#include "move.h"
#include <iostream>




class Game
{
public:
	uint_fast8_t board[49];
	unsigned long long bitboards[4];
	uint_fast8_t turn;

	void print();

	void printbb(unsigned long long bb);

	void clear();

	void move(Move move);

	int winner();
	int score();

	void get_all_moves (uint_fast8_t* start,uint_fast8_t* end, int* moves_num);



};





