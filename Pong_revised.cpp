#include <iostream>
#include <SFML/graphics.hpp>
#include <cstdlib>
#include <cmath>


int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	const float pi = 3.14159f;
	const int WIDTH = 900;
	const int HEIGHT = 600;
	sf::Time ball2ReleaseTime = sf::seconds(3);
	bool isMoving = false;
	bool isPlaying = false;

	sf::RenderWindow PONG(sf::VideoMode(WIDTH, HEIGHT, 32), "Pong", sf::Style::Titlebar | sf::Style::Close);
	PONG.setVerticalSyncEnabled(true);
	

	sf::Vector2f racketSize(20, 100);
	float racketSpeed = 1;
	sf::RectangleShape p1racket;
	p1racket.setSize(racketSize);
	p1racket.setFillColor(sf::Color::Red);
	sf::RectangleShape p2racket;
	p2racket.setSize(racketSize);
	p2racket.setFillColor(sf::Color::Blue);

	float ballSpeed = 0.5;
	float ballRad = 10;
	float ballDia = ballRad * 2;
	float ball1Angle = 0;
	do	{ ball1Angle = (std::rand() % 360) * pi / 180; } while (std::abs(std::cos(ball1Angle)) < 0.7f);
	float ball2Angle = 0;
	do { ball2Angle = (std::rand() % 360) * pi / 180; } while (std::abs(std::cos(ball1Angle)) < 0.7f);
	sf::Vector2f topNormal(0, ballSpeed);
	sf::Vector2f bottomNormal(0, -ballSpeed);
	
	sf::CircleShape ball1;
	ball1.setRadius(ballRad);
	ball1.setFillColor(sf::Color::Cyan);
	float ball1vx = std::cos(ball1Angle) * ballSpeed;
	float ball1vy = std::sin(ball1Angle) * ballSpeed;
	sf::CircleShape ball2;
	ball2.setRadius(ballRad);
	ball2.setFillColor(sf::Color::White);
	float ball2vx = std::cos(ball2Angle) * ballSpeed;
	float ball2vy = std::sin(ball2Angle) * ballSpeed;

	p1racket.setPosition (0, HEIGHT / 2);
	p2racket.setPosition(WIDTH - racketSize.x, HEIGHT / 2);
	ball1.setPosition(WIDTH / 2, HEIGHT / 2);
	ball2.setPosition(WIDTH / 2, HEIGHT / 2);

	sf::Clock clock;
	sf::Clock clock2;
	

	while (PONG.isOpen())
	{
		sf::Event event;
		while (PONG.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				PONG.close();
		}


		int gameTime = clock.restart().asMilliseconds();
		isMoving = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			p1racket.move(0, -racketSpeed * gameTime);
			if (p1racket.getPosition().y < 0)
				p1racket.setPosition(p1racket.getPosition().x, 0);
			isMoving = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			p1racket.move(0, racketSpeed * gameTime);
			if (p1racket.getPosition().y > HEIGHT - racketSize.y)
				p1racket.setPosition(p1racket.getPosition().x, HEIGHT - racketSize.y);
			isMoving = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			p2racket.move(0, -racketSpeed * gameTime);
			if (p2racket.getPosition().y < 0)
				p2racket.setPosition(p2racket.getPosition().x, 0);
			isMoving = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			p2racket.move(0, racketSpeed * gameTime);
			if (p2racket.getPosition().y > HEIGHT - racketSize.y)
				p2racket.setPosition(p2racket.getPosition().x, HEIGHT - racketSize.y);
			isMoving = true;
		}

		sf::Vector2f ball1Movement(ball1vx * gameTime, ball1vy * gameTime);
		ball1.move(ball1Movement);
		if ((ball1.getPosition().y <= 0) || (ball1.getPosition().y >= HEIGHT - ballDia)) {
			ball1vy = -ball1vy;
			ball1Angle = -ball1Angle;
		}

		if ((ball2.getPosition().y <= 0) || (ball2.getPosition().y >= HEIGHT - ballDia)) {
			ball2vy = -ball2vy;
			ball2Angle = -ball2Angle;
		}

		if ((ball1.getPosition().x >= p1racket.getPosition().x + racketSize.x / 2) &&
			(ball1.getPosition().x <= p1racket.getPosition().x + racketSize.x) &&
			(ball1.getPosition().y >= p1racket.getPosition().y - .1) &&
			(ball1.getPosition().y <= p1racket.getPosition().y + racketSize.y + .1))
		{
			if (isMoving)
			{
				ball1Angle = ball1Angle - pi + ((rand() % 6) - 3) / 100;
				ball1vx = std::cos(ball1Angle) * ballSpeed * 1.5f;
				ball1vy = std::sin(ball1Angle) * ballSpeed * 1.5f;
			}
			else
				ball1vx = -ball1vx;
		}

		if ((ball2.getPosition().x >= p1racket.getPosition().x + racketSize.x / 2) &&
			(ball2.getPosition().x <= p1racket.getPosition().x + racketSize.x) &&
			(ball2.getPosition().y >= p1racket.getPosition().y - .1) &&
			(ball2.getPosition().y <= p1racket.getPosition().y + racketSize.y + .1))
		{
			if (isMoving)
			{
				if (ball2.getPosition().y > p1racket.getPosition().y)
				ball2Angle = ball2Angle - pi + ((rand() % 6) - 3) / 100;
				ball2vx = std::cos(ball2Angle) * ballSpeed * 1.5f;
				ball2vy = std::sin(ball2Angle) * ballSpeed * 1.5f;
			}
			else
				ball2vx = -ball2vx;
		}

		if ((ball1.getPosition().x + ballDia >= p2racket.getPosition().x) &&
			(ball1.getPosition().x + ballDia <= p2racket.getPosition().x + racketSize.x / 2) &&
			(ball1.getPosition().y >= p2racket.getPosition().y - .1) &&
			(ball1.getPosition().y <= p2racket.getPosition().y + racketSize.y + .1))
		{
			if (isMoving)
			{
				ball1Angle = ball1Angle - pi + ((rand() % 6) - 3) / 100;
				ball1vx = std::cos(ball1Angle) * ballSpeed * 1.5f;
				ball1vy = std::sin(ball1Angle) * ballSpeed * 1.5f;
			}
			else
				ball1vx = -ball1vx;
		}

		if ((ball2.getPosition().x + ballDia >= p2racket.getPosition().x) &&
			(ball2.getPosition().x + ballDia <= p2racket.getPosition().x + racketSize.x /2) &&
			(ball2.getPosition().y >= p2racket.getPosition().y - .1) &&
			(ball2.getPosition().y <= p2racket.getPosition().y + racketSize.y + .1))
		{
			if (isMoving)
			{
				ball2Angle = ball2Angle - pi + ((rand() % 6) - 3) / 100;
				ball2vx = std::cos(ball2Angle) * ballSpeed * 1.5f;
				ball2vy = std::sin(ball2Angle) * ballSpeed * 1.5f;
			}
			else
				ball2vx = -ball2vx;
		}

		PONG.clear();
		PONG.draw(p1racket);
		PONG.draw(p2racket);
		PONG.draw(ball1);
		if (clock2.getElapsedTime() > ball2ReleaseTime)
		{
			PONG.draw(ball2);
			sf::Vector2f ball2Movement(ball2vx * gameTime, ball2vy * gameTime);
			ball2.move(ball2Movement);

			if (((ball1.getPosition().x >= ball2.getPosition().x) &&
				(ball1.getPosition().x <= ball2.getPosition().x + ballDia) &&
				(ball1.getPosition().y >= ball2.getPosition().y) &&
				(ball1.getPosition().y <= ball2.getPosition().y + ballDia)) ||
				((ball2.getPosition().x >= ball1.getPosition().x) &&
					(ball2.getPosition().x <= ball1.getPosition().x + ballDia) &&
					(ball2.getPosition().y >= ball1.getPosition().y) &&
					(ball2.getPosition().y <= ball1.getPosition().y + ballDia))
				)
			{
				ball1vx = -ball1vx;
				ball2vx = -ball2vx;
			}
		}
		PONG.display();
	}
}

