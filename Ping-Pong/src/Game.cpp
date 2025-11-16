#include "Game.hpp"
#include <sstream>
#include <cmath>

Game::Game(unsigned int width, unsigned int height)
: window(sf::VideoMode(width, height), "Ping Pong"),
windowWidth(width), windowHeight(height),
leftPaddle(50.0f, height / 2.0f, 20.0f, 120.0f, 450.0f),
rightPaddle(width - 50.0f, height / 2.0f, 20.0f, 120.0f, 450.0f),
ball(9.0f),
scoreLeft(0), scoreRight(0), state(GameState::MENU)
{
    window.setFramerateLimit(120);
    loadAssets();
    resetRound();
    rightPaddle.setAIEnabled(true);
}

void Game::loadAssets()
{
    if(!font.loadFromFile("assets/fonts/Ubuntu-M.ttf"))
    {

    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(48);
    scoreText.setPosition(windowWidth/2 - 50, 10);

    titleText.setFont(font);
    titleText.setCharacterSize(36);
    titleText.setString("Ping Pong - Press Enter to Start");
    titleText.setPosition(windowWidth/2 - 320, windowHeight/2 - 40);

    hintText.setFont(font);
    hintText.setCharacterSize(20);
    hintText.setString("W/S to move. Esc to quit.Press R to reset during play");
    hintText.setPosition(10, windowHeight - 30);
}

void Game::resetRound()
{
    leftPaddle.setPosition(50.0f, windowHeight / 2.0f);
    rightPaddle.setPosition(windowWidth - 50.0f, windowHeight / 2.0f);
    ball.reset({static_cast<float>(windowWidth)/2.0f, static_cast<float>(windowHeight)/2.0f}, 360.f);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) window.close();
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape) window.close();
            if(state == GameState::MENU)
            {
                if(event.key.code == sf::Keyboard::Enter)
                {
                    state = GameState::PLAYING;
                    scoreLeft = 0;
                    scoreRight = 0;
                    resetRound();
                }
            }
            else if(state == GameState::PLAYING)
            {
                if (event.key.code == sf::Keyboard::R)
                {
                    scoreLeft = 0;
                    scoreRight = 0;
                    resetRound();
                }
            }
            else if(state == GameState::GAME_OVER)
            {
                if(event.key.code == sf::Keyboard::Enter)
                {
                    state = GameState::MENU;
                }
            }
        }
    }
}

void Game::update(float dt)
{
    if(state != GameState::PLAYING) return;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        leftPaddle.moveUp(dt);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        leftPaddle.moveDown(dt);
    }

    auto clamPaddle = [this](Paddle& p)
    {
        float halfH = p.getBounds().height / 2.0f;
        float y = p.getShape().getPosition().y;
        if(y - halfH < 0)
        {
            p.setPosition(p.getShape().getPosition().x, halfH);
        }
        if(y + halfH > windowHeight)
        {
            p.setPosition(p.getShape().getPosition().x, windowHeight - halfH);
        }
    };

    clamPaddle(leftPaddle);
    clamPaddle(rightPaddle);

    rightPaddle.updateAI(ball.getPosition(), dt);

    ball.update(dt);

    if(ball.getPosition().y - ball.getBounds().height/2.0f <= 0.0f)
    {
        ball.reflectY();
    }
    else if(ball.getPosition().y + ball.getBounds().height/2.0f >= windowHeight)
    {
        ball.reflectY();
    }

    handleCollisions();

    if(ball.getPosition().x < 0.0f)
    {
        scoreRight++;
        if(scoreRight >= 7)
        {
            state = GameState::GAME_OVER;
            titleText.setString("Right Player Wins! Press Enter to return to Menu");
        }
        resetRound();
    }
    else if(ball.getPosition().x > static_cast<float>(windowWidth))
    {
        scoreLeft++;
        if(scoreLeft >= 7)
        {
            state = GameState::GAME_OVER;
            titleText.setString("Left Player Wins! Press Enter to return to Menu");
        }
        resetRound();
    }

    std::ostringstream ss;
    ss << scoreLeft << " : " << scoreRight;
    scoreText.setString(ss.str());

    sf::FloatRect rect = scoreText.getLocalBounds();
    scoreText.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    scoreText.setPosition(windowWidth/2.0f, 40.0f);
}

void Game::handleCollisions()
{
    if(ball.getBounds().intersects(leftPaddle.getBounds()))
    {
        float paddleY = leftPaddle.getShape().getPosition().y;
        float diff = ball.getPosition().y - paddleY;
        float normalized = diff / (leftPaddle.getBounds().height / 2.0f);
        float addY = normalized * 200.0f;
        ball.reflectX(addY);
        ball.increaseSpeed(1.03f);
    }
    if(ball.getBounds().intersects(rightPaddle.getBounds()))
    {
        float paddleY = rightPaddle.getShape().getPosition().y;
        float diff = ball.getPosition().y - paddleY;
        float normalized = diff / (rightPaddle.getBounds().height / 2.0f);
        float addY = normalized * 200.0f;
        ball.reflectX(addY);
        ball.increaseSpeed(1.03f);
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);

    if(state == GameState::MENU)
    {
        window.draw(titleText);
        window.draw(hintText);
    }
    else if(state == GameState::PLAYING || state == GameState::GAME_OVER)
    {
        for (int y = 0; y < static_cast<int>(windowHeight); y += 30)
        {
            sf::RectangleShape segment(sf::Vector2f(4.0f, 20.0f));
            segment.setPosition(windowWidth / 2.0f - 2.0f, static_cast<float>(y));
            window.draw(segment);
        }

        window.draw(leftPaddle.getShape());
        window.draw(rightPaddle.getShape());
        window.draw(ball.getShape());
        window.draw(scoreText);

        if(state == GameState::GAME_OVER)
        {
            window.draw(titleText);
            window.draw(hintText);
        }

    }

    window.display();
}