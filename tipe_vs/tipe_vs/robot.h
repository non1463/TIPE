#pragma once

#include <iostream>
#include "move.h"
#include "game.h"
#include "MCTS.h"
#include <random>

using namespace std;

class Robot
{
public:

	void glouton_search(Game* game);

	void mcts_search(Game* game);
	


	float evaluation;
	Move move;


	Robot();

private:
	int simulate(Game game);
	int simulate2(Game game);
	//random_device rand_dev;
	//mt19937 generator;
	//uniform_int_distribution<int>  distr;


	Move randmove;
	Move test_move;


	uint_fast8_t testmoves_start[300]; // possibles moves for possible moves tree
	uint_fast8_t testmoves_end[300];
	int testmoves_num;

	uint_fast8_t simulatemoves_start[300];
	uint_fast8_t simulatemoves_end[300];
	int moves_num = 0;

	Node* mcts_root = new Node;
	Node* mcts = nullptr;

	Game test_game;
	int best_child_id;
	bool red_side;

	int best_move_id;

};

