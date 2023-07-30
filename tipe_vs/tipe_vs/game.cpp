#include <iostream>
#include "game.h"
#include "move.h"
#include "ataxx.h"
using namespace std;


void Game::clear()
{
	turn = 1;
	bitboards[1] = 0;
	bitboards[2] = 0;
	for(int x = 0; x<7; x++)
	{
		for (int y = 0; y<7; y++)
		{
			if (x == 0 || x== 6)
			{
				if (x == y)
				{
					board[x+7*y] = 1;
					bitboards[1] |= 1ull << (x+7*y);
				}
				else if (x == 6-y)
				{
					board[x+7*y] = 2;
					bitboards[2] |= 1ull << (x+7*y);
				}
				else
					board[x+7*y] = 0;
			}
			else
			{
				board[x+7*y] = 0;
			}
		}
	}
	bitboards[3] = bitboards[1] | bitboards[2];
}


void Game::print()
{
	cout  << " -----------------------------" << endl;
	for (int y = 0; y<7; y++)
	{
		for (int x= 0 ; x<7; x++)
		{
			char e;
			if(board[x+7*y] == 1)
				e = 'O';
			else if (board[x+7*y] == 2)
				e = 'X';
			else
				e = ' ';
			cout <<  " | " << e;
		}
		cout << " |" << endl << " -----------------------------" << endl;
	}
	
}




void Game::move(Move move)
{
	
	unsigned long long bbs = 1ull << move.start, bbe = 1ull << move.end;
	if (move.long_jump)
	{
		board[move.start] = 0; // supprime la piece de depart dans board
		bitboards[turn] ^= bbs; // supprime la piece de depart dans bitboard
		bitboards[3] ^= bbs; // supprime la piece de depart dans bitboard all
	}
	board[move.end] = turn; // ajoute la piece d'arrivée dans board
	bitboards[turn] |= bbe; // ajoute la piece d'arrivée dans bitboard
	bitboards[3] |= bbe; // ajoute la piece d'arrivée dans bitboard all

	//unsigned long long = 
	unsigned long long convert_mask = Ataxx::convertbb[move.end] & bitboards[turn == 1 ? 2 : 1]; 
	uint_fast8_t arr [15];
	Ataxx::extract(convert_mask, arr);
	uint_fast8_t i = 0;
	while (arr[i]!=0xff)
	{
		board[arr[i]] = turn; // convertis les pieces dans board
		i++;
	}
	bitboards[turn] |= convert_mask;// convertis les pieces dans bitboard
	bitboards[turn == 1 ? 2 : 1] ^= convert_mask; // retire les pieces converties dans bitboard

	turn = turn == 1 ? 2 : 1;
	
}




void Game::get_all_moves (uint_fast8_t* start,uint_fast8_t* end, int* moves_num )
{
	int i = 0;
	uint_fast8_t pos_list [40];
	uint_fast8_t moves_list [25];
	Ataxx::extract(bitboards[turn],pos_list);
	int u = 0;
	int v;
	while (pos_list[u] != 0xff)
	{
		Ataxx::extract(Ataxx::movesbb[pos_list[u]] & (~bitboards[3]),moves_list);
		v = 0;
		while (moves_list[v]!=0xff)
		{
			start[i] = pos_list[u];
			end[i] = moves_list[v];
			i++;
			v++;
		}
		u++;
	}
	(*moves_num) = i;
}


int Game::winner()
{
	int win = 0;
	for (int i = 0; i<49; i++)
	{
		if (board[i] == 1)
			win++;
		else if (board[i] == 2)
			win--;
	}
	if (win > 0)
		return 1;
	else if (win < 0)
		return 2;
	else
		return 0;
}

int Game::score()
{
	int win = 0;
	for (int i = 0; i < 49; i++)
	{
		if (board[i] == 1)
			win++;
		else if (board[i] == 2)
			win--;
	}
	return win;
}




void Game::printbb(unsigned long long bb)
{
	cout  << " -----------------------------" << endl;
	for (int y = 0; y<7; y++)
	{
		for (int x= 0 ; x<7; x++)
		{
			char e;
			if(bb & (1ull << (x+7*y)))
				e = '*';
			else
				e = ' ';
			cout <<  " | " << e;
		}
		cout << " |" << endl << " -----------------------------" << endl;
	}
}