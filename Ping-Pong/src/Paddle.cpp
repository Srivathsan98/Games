#include "Paddle.hpp"

Paddle::Paddle(float x, float y, float w, float h, float speed)
: speed(speed), aiEnabled(false)
{
    shape.setSize({w, h});
    shape.setOrigin(w / 2.0f, h / 2.0f);
    shape.setPosition(x, y);
}

void Paddle::update(float dt)
{
    // Paddle movement is handled externally
}

void Paddle::moveUp(float dt)
{
    shape.move(0.0f, -speed * dt);
}

void Paddle::moveDown(float dt)
{
    shape.move(0.0f, speed * dt);
}

void Paddle::setPosition(float x, float y)
{
    shape.setPosition(x, y);
}

void Paddle::setAIEnabled(bool enabled)
{
    aiEnabled = enabled;
}

void Paddle::updateAI(const sf::Vector2f& ballPos, float dt)
{
    if (!aiEnabled) return;

    float targetY = ballPos.y;
    float currentY = shape.getPosition().y;
    float dir = (targetY > currentY) ? 1.0f : -1.0f;

    float diff = std::abs(targetY = currentY);
    float moveSpeed = speed;

    if(diff < 10.0f)
        moveSpeed = speed * 0.4f;
    shape.move(0.0f, dir * moveSpeed * dt);
}

const sf::RectangleShape& Paddle::getShape() const
{
    return shape;
}

sf::FloatRect Paddle::getBounds() const
{
    return shape.getGlobalBounds();
}

float Paddle::getY() const
{
    return shape.getPosition().y;
}