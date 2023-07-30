#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"




class Renderer
{
public:
	sf::Texture t_board;
	sf::RectangleShape s_board;

	sf::Texture t_rules;
	sf::RectangleShape s_rules;

	sf::RectangleShape s_highlight;

	sf::CircleShape s_red, s_blue;

	Renderer();

	void render(sf::RenderWindow& window, Game& game);

	void highlight(uint_fast8_t pos,unsigned short color); // 0 is nothing, 1 is light green , 2 is magenta, 3 is yellow
	// hilighte something alredy highlightd to unhilight it
	void clear_highlight();


private:
	const sf::Color highliting_color[5] = {sf::Color(0,0,0,0),sf::Color(0,255,0,170), sf::Color(255,0,255,170), sf::Color(0,200,255,170), sf::Color(255,200,0,110) };

	unsigned short highliting[49];
};

