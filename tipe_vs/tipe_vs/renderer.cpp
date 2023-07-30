#include "renderer.h"
#include "game.h"
#include <SFML/Graphics.hpp>

#include <iostream>


void Renderer::clear_highlight()
{
	for (int i = 0; i < 49; i++)
	{
		highliting[i] = 0;
	}
}


Renderer::Renderer()
{
	t_board.loadFromFile("ressources/board.png");
	s_board.setTexture(&t_board);
	s_board.setSize(sf::Vector2f(700.f, 700.f));
	s_board.setPosition(sf::Vector2f(0.f, 0.f));

	t_rules.loadFromFile("ressources/rules.png");
	s_rules.setTexture(&t_rules);
	s_rules.setSize(sf::Vector2f(300.f, 700.f));
	s_rules.setPosition(sf::Vector2f(700.f, 0.f));

	s_red.setFillColor(sf::Color::Red);
	s_red.setRadius(40.f);
	s_red.setOrigin(-10, -10);
	s_blue.setFillColor(sf::Color::Blue);
	s_blue.setRadius(40.f);
	s_blue.setOrigin(-10, -10);


	s_highlight.setSize(sf::Vector2f(100, 100));
	clear_highlight();

}




void Renderer::highlight(uint_fast8_t pos, unsigned short color)
{
	highliting[pos] = color;
}

void Renderer::render(sf::RenderWindow& window, Game& game)
{

	window.clear();
	window.draw(s_board);
	window.draw(s_rules);

	if (game.turn == 1)
	{
		s_red.setPosition(800, 500);
		window.draw(s_red);
	}
	else
	{
		s_blue.setPosition(800, 500);
		window.draw(s_blue);
	}

	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			int i = x + 7 * y;
			if (game.board[i] == 1)
			{
				s_red.setPosition(x * 100, y * 100);
				window.draw(s_red);
			}
			else if (game.board[i] == 2)
			{
				s_blue.setPosition(x * 100, y * 100);
				window.draw(s_blue);
			}


			if (highliting[i] != 0)
			{
				s_highlight.setFillColor(highliting_color[highliting[i]]);
				s_highlight.setPosition(x * 100, y * 100);
				window.draw(s_highlight);
			}
		}
	}
	window.display();
	// print board
	//print pieces

}

