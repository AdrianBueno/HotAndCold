#include "Entity.h"

Entity::Entity(float x, float y)
    : posX(x), posY(y) {
}



bool Entity::CheckCollisionWithEntity(const Entity& other) const {
    SDL_Rect otherRect = other.GetHitbox();
    SDL_Rect myRect = { static_cast<int>(posX), static_cast<int>(posY), hitbox.w, hitbox.h };

    return SDL_HasIntersection(&myRect, &otherRect);
}


