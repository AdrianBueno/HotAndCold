#include "Projectile.h"
#include <SDL.h>

/// @brief Constructor del proyectil.
/// @param x Posición inicial X.
/// @param y Posición inicial Y.
/// @param dirX Dirección horizontal normalizada.
/// @param dirY Dirección vertical normalizada.
/// @param speed Velocidad de movimiento en píxeles por segundo.
/// @param maxLifetime Tiempo máximo de vida en segundos.
Projectile::Projectile(float x, float y, float dirX, float dirY, float speed, float maxLifetime)
    : Entity(x, y), dirX(dirX), dirY(dirY), speed(speed), maxLifetime(maxLifetime) {
    // Hitbox pequeño y cuadrado estándar
    hitbox = { 0, 0, 8, 8 };
}

/// @brief Actualiza el proyectil (movimiento, colisión, vida).
/// Se mueve en línea recta, colisiona con el mapa y se destruye si es necesario.
/// @param deltaTime Tiempo entre frames.
/// @param map Referencia al mapa.
void Projectile::Update(float deltaTime, CommandQueue& queue) {
    // Movimiento
    float newX = posX + dirX * speed * deltaTime;
    float newY = posY + dirY * speed * deltaTime;

    // Comprobación simple de colisión con el mapa
    SDL_Rect futureRect = {
        static_cast<int>(newX),
        static_cast<int>(newY),
        hitbox.w,
        hitbox.h
    };

    // Obtención de tiles ocupados
    /*int tileSize = world.GetTileSize();
    int tileLeft = futureRect.x / tileSize;
    int tileRight = (futureRect.x + futureRect.w - 1) / tileSize;
    int tileTop = futureRect.y / tileSize;
    int tileBottom = (futureRect.y + futureRect.h - 1) / tileSize;

    bool collided = false;
    for (int ty = tileTop; ty <= tileBottom; ++ty) {
        for (int tx = tileLeft; tx <= tileRight; ++tx) {
            if (world.IsSolidAt(tx, ty)) {
                collided = true;
                break;
            }
        }
        if (collided) break;
    }

    if (collided) {
        isActive = false; // Destruir el proyectil
        return;
    }

    // Movimiento si no hay colisión
    posX = newX;
    posY = newY;

    // Actualización del tiempo de vida
    lifetime += deltaTime;
    if (lifetime >= maxLifetime) {
        isActive = false;
    }*/
}

/// @brief Renderiza el proyectil como un rectángulo blanco.
/// @param renderer Renderer SDL.
/// @param cameraViewport Viewport/cámara actual.
void Projectile::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) {
    SDL_Rect screenRect = {
        static_cast<int>(posX) - cameraViewport.x,
        static_cast<int>(posY) - cameraViewport.y,
        hitbox.w,
        hitbox.h
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco para proyectiles
    SDL_RenderFillRect(renderer, &screenRect);
}
