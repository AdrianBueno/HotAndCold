// CommandSpawnProjectile.h
#pragma once
#include "Command.h"
#include "../../Entities/Projectile.h"
#include "../EntityManager.h"

/// @brief Comando para spawnear un proyectil.
class CommandSpawnProjectile : public Command {
public:
    CommandSpawnProjectile(float x, float y, float dirX, float dirY, float speed, float lifetime)
        : x(x), y(y), dirX(dirX), dirY(dirY), speed(speed), lifetime(lifetime) {
    }

    void Execute(EntityManager& entityManager) override {
        auto proj = std::make_unique<Projectile>(x, y, dirX, dirY, speed, lifetime);
        entityManager.Add(std::move(proj));
    }

private:
    float x, y, dirX, dirY, speed, lifetime;
};
