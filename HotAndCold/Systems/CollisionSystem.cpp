#include "CollisionSystem.h"
#include <SDL.h>

bool CollisionSystem::WouldCollideWithWorld(const Entity& entity, float newX, float newY, const IWorld& world) {
    int mapWidthPixels = world.GetWidth() * world.GetTileSize();
    int mapHeightPixels = world.GetHeight() * world.GetTileSize();

    

    SDL_Rect futureRect = {
        static_cast<int>(newX),
        static_cast<int>(newY),
        entity.GetHitbox().w,
        entity.GetHitbox().h
    };

    int tileSize = world.GetTileSize();

    int tileLeft = futureRect.x / tileSize;
    int tileRight = (futureRect.x + futureRect.w - 1) / tileSize;
    int tileTop = futureRect.y / tileSize;
    int tileBottom = (futureRect.y + futureRect.h - 1) / tileSize;

    for (int ty = tileTop; ty <= tileBottom; ++ty) {
        for (int tx = tileLeft; tx <= tileRight; ++tx) {
            if (world.IsSolidAt( tx, ty)) {
                return true;
            }
        }
    }
    
    // Clamp la posición para que no pueda salir del mundo
    if (newX < 0 || newY < 0 ||
        newX + futureRect.w > mapWidthPixels ||
        newY + futureRect.h > mapHeightPixels) {
        return true;
    }

    return false;
}

bool CollisionSystem::WouldCollideWithEntities(const Entity& entity, float newX, float newY, const std::vector<std::unique_ptr<Entity>>& entities) {
    SDL_Rect futureRect = {
        static_cast<int>(newX),
        static_cast<int>(newY),
        entity.GetHitbox().w,
        entity.GetHitbox().h
    };

    for (const auto& other : entities) {
        if (other.get() == &entity) continue;

        SDL_Rect otherRect = {
            static_cast<int>(other->GetX()),
            static_cast<int>(other->GetY()),
            other->GetHitbox().w,
            other->GetHitbox().h
        };

        if (SDL_HasIntersection(&futureRect, &otherRect)) {
            return true;
        }
    }

    return false;
}
