#include "Ball.h"
#include <SFML/System.hpp>

Ball::Ball(sf::Vector2f pos, float sz, float rotation)
{
	_rotation = rotation;
	_position = pos;
	_size = sz;
	_color = sf::Color::White;
	_shape.setFillColor(_color);
	_shape.setRadius(_size);
	_shape.setPosition(_position);
	_shape.setOutlineThickness(0);
	_shape.setOrigin(_size, _size);
	if (!_texture.loadFromFile("SoccerBall.png"))
		printf("%s", "Texture not loaded properly! Error!");
	_shape.setTexture(&_texture);
	_shape.setTextureRect(sf::IntRect(0, 0, 99, 96));
	_deltaY = 1.0f;
}


Ball::~Ball()
{
}

collisionSide Ball::checkCollisionWithBoundaries(sf::Vector2i boundaries)
{
	if (_position.x - _size < 0) return LEFT; 
	else if (_position.x + _size > boundaries.x) return RIGHT; 
	else if (_position.y - _size < 0) return TOP; 
	else if (_position.y + _size > boundaries.y) return BOTTOM;
	else return NONE;
}

void Ball::onMouseDrag(sf::RenderWindow &x)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && sf::Mouse::getPosition(x).x > (int)_position.x - _size / 2 && sf::Mouse::getPosition(x).x < (int)_position.x + _size / 2
		&& sf::Mouse::getPosition(x).y >(int)_position.y - _size / 2 && sf::Mouse::getPosition(x).y < (int)_position.y + _size / 2)
	{
		printf("%i %i \n", sf::Mouse::getPosition(x).x, sf::Mouse::getPosition(x).y);
		_position = (sf::Vector2f)sf::Mouse::getPosition(x);
		_isDragged = true;
	}
}

void Ball::update(sf::RenderWindow &wind, sf::Vector2i boundaries)
{
	_deltaY += GRAVITY;
	_position = sf::Vector2f(_position.x, _position.y + _deltaY);
	_shape.rotate(_rotation);
	onMouseDrag(wind);
	if (checkCollisionWithBoundaries(boundaries) == BOTTOM) {
		_deltaY = _deltaY * -0.5f;
		_position = sf::Vector2f(_position.x, _position.y + _deltaY * 2 - _size / 2);
	}
	else if (checkCollisionWithBoundaries(boundaries) == LEFT) printf("%s\n", "LEFT Collision detected...");
	else if (checkCollisionWithBoundaries(boundaries) == RIGHT) printf("%s\n", "RIGHT Collision detected...");
	else if (checkCollisionWithBoundaries(boundaries) == TOP) printf("%s\n", "TOP Collision detected...");
	_shape.setPosition(_position);

	// printf("%f %f \n", _position.x, _position.y);
	// It must be another function - let leave as it is for now ;-)
	wind.draw(_shape);
}
