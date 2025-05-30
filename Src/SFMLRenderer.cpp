#include "SFMLRenderer.h"

SFMLRenderer::SFMLRenderer(Game& game) : game(game) {
    ballShape.setRadius(30.0f);
    ballShape.setFillColor(sf::Color::Yellow);
    ballShape.setOrigin(30.0f, 30.0f);

    // 🔹 Crear bordes visibles
    leftWall.setSize(sf::Vector2f(10.0f, 600.0f));
    leftWall.setFillColor(sf::Color::Blue);
    leftWall.setPosition(50, 0);

    rightWall.setSize(sf::Vector2f(10.0f, 600.0f));
    rightWall.setFillColor(sf::Color::Blue);
    rightWall.setPosition(740, 0);

    floor.setSize(sf::Vector2f(800.0f, 10.0f));
    floor.setFillColor(sf::Color::Red);
    floor.setPosition(0, 590);

    ceiling.setSize(sf::Vector2f(800.0f, 10.0f));
    ceiling.setFillColor(sf::Color::Red);
    ceiling.setPosition(0, 0);

    // 🔹 Crear representación visual de obstáculos
    for (auto obstacle : game.GetObstacles()) {
        sf::RectangleShape shape(sf::Vector2f(60.0f, 60.0f));
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(30.0f, 30.0f);
        obstacleShapes.push_back(shape);
    }
}

void SFMLRenderer::Render(sf::RenderWindow& window) {
    b2Vec2 ballPos = game.GetBall()->GetPosition();
    float scale = 30.0f;

    ballShape.setPosition(ballPos.x * scale + 400, 600 - ballPos.y * scale);

    // 🔹 Dibujar bordes
    window.draw(leftWall);
    window.draw(rightWall);
    window.draw(floor);
    window.draw(ceiling);

    // 🔹 Dibujar obstáculos
    for (size_t i = 0; i < obstacleShapes.size(); i++) {
        b2Vec2 pos = game.GetObstacles()[i]->GetPosition();
        obstacleShapes[i].setPosition(pos.x * scale + 400, 600 - pos.y * scale);
        window.draw(obstacleShapes[i]);
    }

    window.draw(ballShape);
}
