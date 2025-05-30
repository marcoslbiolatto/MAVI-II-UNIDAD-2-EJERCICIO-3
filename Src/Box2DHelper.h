#ifndef BOX2DHELPER_H
#define BOX2DHELPER_H

#include <Box2D/Box2D.h>

namespace Box2DHelper {
    inline b2World* CreateWorld() {
        static b2Vec2 gravity(0.0f, 0.0f); // 🔹 Sin gravedad, para rebote libre
        static b2World world(gravity);
        return &world;
    }

    inline b2Body* CreateStaticBox(b2World* world, float x, float y, float width, float height) {
        b2BodyDef bodyDef;
        bodyDef.position.Set(x, y);
        b2Body* body = world->CreateBody(&bodyDef);
        b2PolygonShape box;
        box.SetAsBox(width / 2.0f, height / 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 0.5f;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 1.0f; // 🔹 Rebote fuerte
        body->CreateFixture(&fixtureDef);

        return body;
    }

    inline b2Body* CreateStaticObstacle(b2World* world, float x, float y, float width, float height) {
        return CreateStaticBox(world, x, y, width, height);
    }

    inline b2Body* CreateDynamicBall(b2World* world, float x, float y, float radius) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(y, x);
        bodyDef.bullet = true; 
        b2Body* body = world->CreateBody(&bodyDef);

        b2CircleShape circle;
        circle.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = 0.9f;
        fixtureDef.friction = 0.8f; // 🔹 Menos fricción para mantener movimiento fluido
        fixtureDef.restitution = 1.0f; // 🔹 Rebote más dinámico
        body->CreateFixture(&fixtureDef);

        return body;
    }
}

#endif
