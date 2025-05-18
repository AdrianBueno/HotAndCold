#include "EntityManager.h"
#include <algorithm> // std::remove_if
#include <iostream>
#include "Commands/CommandQueue.h"
#include "../Systems/CollisionSystem.h"

EntityManager::EntityManager() {
    std::cout << "[EntityManager] Initialized." << std::endl;
}

EntityManager::~EntityManager() {
    Clear();
    std::cout << "[EntityManager] Cleaned." << std::endl;
}

void EntityManager::Add(std::unique_ptr<Entity> entity) {
    if (Player* p = dynamic_cast<Player*>(entity.get())) {
        player = p;
    }
    entities.push_back(std::move(entity));
}

/// @brief Actualiza todas las entidades activas.
/// Las entidades inactivas son eliminadas de manera segura.
void EntityManager::Update(float deltaTime, const IWorld& world, CommandQueue& commandQueue) {
    // Actualizar todas las entidades activas
    for (auto& entity : entities) {
        if (entity->IsActive()) {
            float previousX = entity->GetX();
            float previousY = entity->GetY();
            entity->Update(deltaTime, commandQueue);
            if (CollisionSystem::WouldCollideWithWorld(*entity, entity->GetX(), entity->GetY(), world)) {
                entity->SetX(previousX);
                entity->SetY(previousY);
            }
        }
    }
    this->CheckEntityCollisions();

    // Eliminar entidades inactivas de manera segura
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](const std::unique_ptr<Entity>& e) { return !e->IsActive(); }),
        entities.end()
    );
}

/// @brief Renderiza todas las entidades activas.
void EntityManager::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) {
    for (auto& entity : entities) {
        if (entity->IsActive()) {
            entity->Render(renderer, cameraViewport);
        }
    }
}

/// @brief Comprueba colisiones entre todas las entidades activas.
/// Si hay colisión, llama a OnCollision de ambas entidades.
void EntityManager::CheckEntityCollisions() {
    if (!player || !player->IsActive()) return;

    SDL_Rect playerHitbox = player->GetHitbox();

    for (const auto& entityPtr : entities) {
        Entity* other = entityPtr.get();
        if (other == player || !other->IsActive()) continue;

        SDL_Rect otherHitbox = other->GetHitbox();

        if (SDL_HasIntersection(&playerHitbox, &otherHitbox)) {
            player->OnCollision(*other);
            other->OnCollision(*player);
        }
    }
}

/// @brief Elimina todas las entidades actuales (vacía el vector).
void EntityManager::Clear() {
    entities.clear();
}
