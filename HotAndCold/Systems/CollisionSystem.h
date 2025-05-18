#pragma once

#include <vector>
#include "../Entities/Entity.h"
#include "../Map/IWorld.h"

class CollisionSystem {
public:
    /// @brief Comprueba si una entidad colisionar�a en una posici�n dada con el mundo.
    /// @param entity Entidad a comprobar.
    /// @param newX Nueva posici�n X.
    /// @param newY Nueva posici�n Y.
    /// @param world Referencia al mundo.
    /// @return true si habr�a colisi�n.
    static bool WouldCollideWithWorld(const Entity& entity, float newX, float newY, const IWorld& world);

    /// @brief Comprueba si una entidad colisiona con otras entidades.
    /// @param entity Entidad a comprobar.
    /// @param entities Lista de entidades a comprobar.
    /// @return true si hay colisi�n con alguna entidad.
    static bool WouldCollideWithEntities(const Entity& entity, float newX, float newY, const std::vector<std::unique_ptr<Entity>>& entities);
};
