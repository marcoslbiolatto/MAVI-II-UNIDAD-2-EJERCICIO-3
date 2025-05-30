#include "Game.h"

Game::Game() {
    world = Box2DHelper::CreateWorld();

    // 🔹 Crear barreras en los bordes de la pantalla
    Box2DHelper::CreateStaticBox(world, -12.0f, 0.0f, 1.0f, 20.0f);
    Box2DHelper::CreateStaticBox(world, 12.0f, 0.0f, 1.0f, 20.0f);
    Box2DHelper::CreateStaticBox(world, 0.0f, -10.0f, 24.0f, 1.0f);
    Box2DHelper::CreateStaticBox(world, 0.0f, 10.0f, 24.0f, 1.0f);

    // 🔹 Colocar los obstáculos en posiciones más altas
    obstacles.push_back(Box2DHelper::CreateStaticObstacle(world, -5.0f, 5.0f, 2.0f, 2.0f));  // Más arriba
    obstacles.push_back(Box2DHelper::CreateStaticObstacle(world, 5.0f, 6.0f, 2.5f, 2.5f));   // Más arriba
    obstacles.push_back(Box2DHelper::CreateStaticObstacle(world, 0.0f, 7.0f, 3.0f, 3.0f));   // Más arriba

    // 🔹 Crear pelota en el centro
    ball = Box2DHelper::CreateDynamicBall(world, 0.0f, 0.0f, 1.0f);
    ball->SetBullet(true);
    ball->SetLinearVelocity(b2Vec2(-1.0f, -1.0f));
}


void Game::Update() {
    world->Step(1.0f / 60.0f, 8, 3);

    b2Vec2 velocity = ball->GetLinearVelocity();
    float speedLimit = 0.5f;  // 🔹 Velocidad mínima antes de aplicar impulso
    float minImpulse = 0.2f;  // 🔹 Impulso mínimo para corregir rebotes estáticos

    // 🔹 Si la velocidad es muy baja, aplicamos un impulso sutil para mantener movimiento dinámico
    if (std::abs(velocity.x) < speedLimit || std::abs(velocity.y) < speedLimit) {
        float impulseX = velocity.x < speedLimit ? minImpulse * (velocity.x >= 0 ? 1 : -1) : 0;
        float impulseY = velocity.y < speedLimit ? minImpulse * (velocity.y >= 0 ? 1 : -1) : 0;

        ball->ApplyLinearImpulseToCenter(b2Vec2(impulseX, impulseY), true);
    }
}

b2Body* Game::GetBall() { return ball; }
std::vector<b2Body*> Game::GetObstacles() { return obstacles; }
