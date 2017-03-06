#pragma once
#include <SFML/Graphics.hpp>

enum collisionSide { NONE, LEFT, RIGHT, TOP, BOTTOM };

class Ball
{
public:
	Ball(sf::Vector2f pos, float sz, float rotation);
	~Ball();

	collisionSide checkCollisionWithBoundaries(sf::Vector2i boundaries);
	void onMouseDrag(sf::RenderWindow &x);
	void update(sf::RenderWindow &wind, sf::Vector2i boundaries);

private:
	const float GRAVITY = 0.02f;
	float _size;
	float _rotation;
	float _deltaY;
	sf::CircleShape _shape;
	sf::Vector2f _position;
	sf::Color _color;
	sf::Texture _texture;
	bool _isDragged = false;
};

