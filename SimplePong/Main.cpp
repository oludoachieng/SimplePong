//Include all the header files to avoid errors
#include <SFML/Graphics.hpp> 
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#include <iostream>
#include<time.h>

int main()
{
	srand(time(NULL));//Shall be used for randomizing the position of puck at start

	int puckDx = 1, puckDy = 1, paddleDx = 0, speed = 2;//Variables during game

	sf::RenderWindow window(sf::VideoMode(400, 400), "Simple pong");
	window.setFramerateLimit(60);

	sf::RectangleShape puck(sf::Vector2f(20, 20));//Set up the puck as a rect shape
	puck.setFillColor(sf::Color::Blue);
	puck.setPosition(sf::Vector2f(rand() % 300, rand() % 300));

	sf::RectangleShape paddle(sf::Vector2f(60, 20));//Set up the paddle as a rect shape
	paddle.setFillColor(sf::Color::Red);
	paddle.setPosition(sf::Vector2f(200, 380));


	while (window.isOpen())
	{

		sf::Vector2f paddlePos = paddle.getPosition();

		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black); // clear window for each frame

		puck.move(speed * puckDx, speed * puckDy); //Move puck 

		//check for boundaries x<0,x>380,y<0,y>360
		//change direction of puck upon hitting a boundary

		if (puck.getPosition().x < 0 || puck.getPosition().x > 380)
			puckDx *= -1;

		if (puck.getPosition().y < 0)
			puckDy *= -1;

		if (puck.getPosition().y > 380)
			puckDy = puckDx = 0;

		//If it hits paddle also change direction and puck on right
		if (puck.getPosition().y > 360)
			if (puck.getPosition().x > paddle.getPosition().x)
				if ((puck.getPosition().x - paddle.getPosition().x) < 60)
					puckDy *= -1;

		//if puck passes level of paddle, automatically fails
				else if ((puck.getPosition().x - paddle.getPosition().x) > 60 &&
					(puck.getPosition().x - paddle.getPosition().x) < 80)
				{
					puckDy = puckDx = 0;
					puck.setPosition(puck.getPosition().x, 380);
				}

		//If it hits paddle also change direction and puck on left
		if (puck.getPosition().y > 360)
			if (paddle.getPosition().x > puck.getPosition().x)
				if ((paddle.getPosition().x - puck.getPosition().x) < 20)
					puckDy *= -1;
		//if puck passes level of paddle, automatically fails
				else if ((puck.getPosition().x - paddle.getPosition().x) > 20 &&
					(puck.getPosition().x - paddle.getPosition().x) < 40)
				{
					puckDy = puckDx = 0;
					puck.setPosition(puck.getPosition().x, 380);
				}



		//Space bar shall be used to restart the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			paddle.setPosition(sf::Vector2f(200, 380));
			puck.setPosition(sf::Vector2f(rand() % 300, rand() % 300));
			puckDx = puckDy = 1;
		}


		//Right key shall be used to move paddle to right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (paddlePos.x < 400 - 60)
			{
				paddleDx = speed;
				paddle.setPosition(paddlePos.x + paddleDx, 380);
			}
			else
			{
				paddleDx = 0;
				paddle.setPosition(paddlePos.x + paddleDx, 380);
			}
		}

		//Left key shall be used to move paddle to left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (paddlePos.x > 0)
			{
				paddleDx = -speed;
				paddle.setPosition(paddlePos.x + paddleDx, 380);
			}
			else
			{
				paddleDx = 0;
				paddle.setPosition(paddlePos.x + paddleDx, 380);
			}
		}


		window.draw(puck);
		window.draw(paddle);
		window.display();
	}

	return 0;
}