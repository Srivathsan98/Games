#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
    public:
    Ball(float radius = 8.0f);

    void reset(const sf::Vector2f& center, float speedBase = 300.0f);
    void update(float dt);
    void setPosition(const sf::Vector2f& pos);
    const sf::CircleShape& getShape() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    void reflectX(float addY = 0.0f);
    void reflectY();
    void increaseSpeed(float factor);

    private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;
};