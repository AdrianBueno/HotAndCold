#pragma once

#include <vector>
#include "../Entities/Entity.h"
#include "../Map/IWorld.h"

class CollisionSystem {
public:
    /// @brief Comprueba si una entidad colisionaría en una posición dada con el mundo.
    /// @param entity Entidad a comprobar.
    /// @param newX Nueva posición X.
    /// @param newY Nueva posición Y.
    /// @param world Referencia al mundo.
    /// @return true si habría colisión.
    static bool WouldCollideWithWorld(const Entity& entity, float newX, float newY, const IWorld& world);

    /// @brief Comprueba si una entidad colisiona con otras entidades.
    /// @param entity Entidad a comprobar.
    /// @param entities Lista de entidades a comprobar.
    /// @return true si hay colisión con alguna entidad.
    static bool WouldCollideWithEntities(const Entity& entity, float newX, float newY, const std::vector<std::unique_ptr<Entity>>& entities);
};
