#include "robot.h"


Robot::Robot()
{
	//mt19937 generator (rand_dev());
	//uniform_int_distribution<int>  distr (0, 10000000000000000000);
	//cout << "init" << endl;

	srand(time(NULL));
}


int Robot::simulate(Game game)
{
	while (1)
	{
		game.get_all_moves(simulatemoves_start, simulatemoves_end, &moves_num);
		if (moves_num == 0)
		{
			return game.winner();
		}
		int i = rand() % moves_num;
		randmove.set(simulatemoves_start[i], simulatemoves_end[i]);

		game.move(randmove);
	}
}

int Robot::simulate2(Game game)
{
	while (1)
	{
		game.get_all_moves(simulatemoves_start, simulatemoves_end, &moves_num);
		if (moves_num == 0)
		{
			return game.winner();
		}
		glouton_search(&game);
		game.move(move);
	}
}






void Robot::mcts_search(Game* refgame)
{
	// initialisation
	bool red_side = refgame->turn == 1;

	best_child_id = 0;


	int itterations = 10000;
	// starting of the algorythm
	for (int i = 0; i < itterations; i++)
	{
		//cout << i << endl;
		mcts = mcts_root; // on initialise a la racine de l'arbre
		test_game = *refgame;


		while (mcts->childs_nb != 0) // on recupere la feuille a simuler
		{
			best_child_id = mcts->getMaxUcb1Child();
			mcts = mcts->childs[best_child_id];
			test_game.get_all_moves(testmoves_start, testmoves_end, &testmoves_num);
			test_move.set(testmoves_start[best_child_id], testmoves_end[best_child_id]);
			test_game.move(test_move);
		}

		if (mcts->n != 0) // expand 
		{
			test_game.get_all_moves(testmoves_start, testmoves_end, &testmoves_num);
			if (testmoves_num == 0)
			{
				//test_game.print();
				//cout << (test_game.winner() == refgame->turn) << endl;
				mcts->back_propagate(test_game.winner() == refgame->turn);
				continue;
			}
			mcts->childs_nb = testmoves_num;
			for (int j = 0; j < testmoves_num; j++)
			{
				mcts->childs[j] = new Node;
				mcts->childs[j]->parent = mcts;
			}

			mcts = mcts->childs[0];

			test_move.set(testmoves_start[0], testmoves_end[0]);
			test_game.move(test_move);

		}
		// then we search


		mcts->back_propagate(simulate2(test_game) == refgame->turn); ////////////////////////////////////


	}


	// out
	refgame->get_all_moves(testmoves_start, testmoves_end, &testmoves_num);
	evaluation = 0.f;
	for (int i = 0; i < testmoves_num; i++)
	{
		cout << mcts_root->childs[i]->val() << endl;
		if (mcts_root->childs[i]->val() > evaluation)
		{
			evaluation = mcts_root->childs[i]->val();
			best_move_id = i;
		}
	}
	move.set(testmoves_start[best_move_id], testmoves_end[best_move_id]);
	mcts_root->clear();
}






void Robot::glouton_search(Game* refgame)
{
	bool red_side = refgame->turn == 1;
	refgame->get_all_moves(testmoves_start, testmoves_end, &testmoves_num);
	evaluation = -10.f;
	float eval;
	int possibilities = 0;
	int best_moves_id[300];
	for (int i = 0; i<testmoves_num; i++)
	{
		test_game = *refgame;
		test_move.set(testmoves_start[i], testmoves_end[i]);
		test_game.move(test_move);
		eval = test_game.score();
		if (!red_side)
		{
			eval = -eval;
		}
		eval /= 49.f;
		if (eval > evaluation)
		{
			evaluation = eval;
			best_moves_id[0] = i;
			possibilities= 1;
		}
		else if (eval == evaluation)
		{
			best_moves_id[possibilities] = i;
			possibilities++;
		}
	}


	
	int i = rand() % possibilities;


	move.set(testmoves_start[best_moves_id[i]], testmoves_end[best_moves_id[i]]);
	
}



