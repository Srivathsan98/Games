#include "Ball.hpp"
#include <cmath>
#include <random>

Ball::Ball(float radius) : shape(radius), velocity(0.0f, 0.0f), speed(300.0f)
{
    shape.setOrigin(radius, radius);
}

void Ball::reset(const sf::Vector2f& center, float speedBase)
{
    shape.setPosition(center);
    speed = speedBase;
    static std::mt19937 rng((unsigned)std::random_device{}());
    std::uniform_real_distribution<float> angDist(-0.25f, 0.25f);
    std::uniform_int_distribution<int> side(0,1);
    float angle = angDist(rng);
    float dir = side(rng) == 0 ? -1.0f : 1.0f;
    velocity.x = dir * std::cos(angle) * speed;
    velocity.y = std::sin(angle) * speed;
}

void Ball::update(float dt)
{
    shape.move(velocity * dt);
}

void Ball::setPosition(const sf::Vector2f& pos)
{
    shape.setPosition(pos);
}

const sf::CircleShape& Ball::getShape() const
{
    return shape;
}

sf::FloatRect Ball::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const
{
    return shape.getPosition();
}

sf::Vector2f Ball::getVelocity() const
{
    return velocity;
}

void Ball::reflectX(float addY)
{
    velocity.x = -velocity.x;
    velocity.y += addY;

    float vlen = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if(vlen != 0.0f)
    {
        velocity = (velocity / vlen) * speed;
    }
}

void Ball::reflectY()
{
    velocity.y = -velocity.y;
}

void Ball::increaseSpeed(float factor)
{
    speed *= factor;

    float vlen = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if(vlen != 0.0f)
    {
        velocity = (velocity / vlen) * speed;
    }
}