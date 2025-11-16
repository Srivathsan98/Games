#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Paddle
{
public:
    Paddle(float x, float y, float w, float h, float speed);

    void update(float dt);
    void moveUp(float dt);
    void moveDown(float dt);
    void setPosition(float x, float y);
    void setAIEnabled(bool enabled);
    void updateAI(const sf::Vector2f &ballPos, float dt);
    const sf::RectangleShape &getShape() const;
    sf::FloatRect getBounds() const;
    float getY() const;

private:
    sf::RectangleShape shape;
    float speed;
    bool aiEnabled;
};