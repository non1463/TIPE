#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "game.h"
#include "move.h"
#include "renderer.h"
#include "MCTS.h"
#include "robot.h"


#include <Windows.h>
using namespace std;

#define u8 uint_fast8_t


const u8 empty = 0, white = 1, black = 2, all = 3;





// init renderer
Renderer renderer;


// initialize rand generator







// creating game
Game game;


Robot robot;




int main()
{

	sf::RenderWindow window(sf::VideoMode(1000, 700), "ATAXX");


	bool click = false;
	sf::Vector2i mouse;

	bool robot_play = false;

	u8 select = 49;
	bool movesfomselect[49];
	
	const int search_deep = 1;

	Move move;
	uint_fast8_t moves_start[300];
	uint_fast8_t moves_end[300];
	int moves_num;
	

	game.clear();

	game.get_all_moves(moves_start, moves_end, &moves_num);

	//thread robot_th(robot, &game, search_deep, &renderer);



	bool running = true;
	
	while (running) // main loop
	{
		//system("cls");
		//game.print();



		if (robot_play)
		{
			robot.mcts_search(&game);
			cout << "eval : " << robot.evaluation << endl;
			game.move(robot.move);
			game.get_all_moves(moves_start, moves_end, &moves_num);
			renderer.clear_highlight();
			renderer.highlight(robot.move.start, 4u);
			renderer.highlight(robot.move.end, 4u);

			game.get_all_moves(moves_start, moves_end, &moves_num);
			if (moves_num == 0)
			{
				renderer.render(window, game);
				cout << "\n\nand the winner is : " << (game.winner() == 1 ? "red" : "blue") << endl;
				running = false;
				int uwu; cin >> uwu;
			}
		}

		renderer.render(window, game);
		

		


		if (click)
		{
			u8 x = mouse.x / 100u;
			u8 y = mouse.y / 100u;
			u8 i = x + 7 * y;
			if (game.board[i] == game.turn)
			{
				if (select != 49)
				{
					renderer.clear_highlight();
				}
				renderer.highlight(i, 2u);
				select = i;
				for (int k = 0; k < 49; k++)
				{
					movesfomselect[k] = false;
				}
				for (int k = 0; k < moves_num; k++)
				{
					if (moves_start[k] == select)
					{
						int dist = abs(moves_end[k] - select);
						if (dist == 1 || dist == 6 || dist == 7 || dist == 8)
						{
							renderer.highlight(moves_end[k], 1u);
						}
						else
						{
							renderer.highlight(moves_end[k], 3u);
						}
						movesfomselect[moves_end[k]] = true;
					}
				}
			}
			else if (select != 49 && movesfomselect[i] == true)
			{
				move.set(select, i);
				game.move(move);
				renderer.clear_highlight();
				select = 49u;
				game.get_all_moves(moves_start, moves_end, &moves_num);
				if (moves_num == 0)
				{
					renderer.render(window, game);
					cout << "\n\nand the winner is : " << (game.winner() == 1 ? "red" : "blue") << endl;
					running = false;
					int uwu; cin >> uwu;
				}
			}
			else
			{
				renderer.clear_highlight();
				select = 49u;
			}
		}


		robot_play = false;
		click = false;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				click = true;
				mouse = sf::Mouse::getPosition(window);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				robot_play = true;
			}
		}
	}



	


	window.close();

	return 0;
}
