#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Paddle.hpp"
#include <string>

enum class GameState
{
    MENU,
    PLAYING,
    GAME_OVER
};

class Game
{
    public:
    Game(unsigned int width = 1024, unsigned int height = 768);
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    void resetRound();
    void handleCollisions();
    void loadAssets();

    sf::RenderWindow window;
    unsigned int windowWidth, windowHeight;

    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;

    sf::Font font;
    sf::Text scoreText;
    sf::Text titleText;
    sf::Text hintText;

    int scoreLeft;
    int scoreRight;

    GameState state;

    sf::Clock clock;
};