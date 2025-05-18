#include "Projectile.h"
#include <SDL.h>

/// @brief Constructor del proyectil.
/// @param x Posici�n inicial X.
/// @param y Posici�n inicial Y.
/// @param dirX Direcci�n horizontal normalizada.
/// @param dirY Direcci�n vertical normalizada.
/// @param speed Velocidad de movimiento en p�xeles por segundo.
/// @param maxLifetime Tiempo m�ximo de vida en segundos.
Projectile::Projectile(float x, float y, float dirX, float dirY, float speed, float maxLifetime)
    : Entity(x, y), dirX(dirX), dirY(dirY), speed(speed), maxLifetime(maxLifetime) {
    // Hitbox peque�o y cuadrado est�ndar
    hitbox = { 0, 0, 8, 8 };
}

/// @brief Actualiza el proyectil (movimiento, colisi�n, vida).
/// Se mueve en l�nea recta, colisiona con el mapa y se destruye si es necesario.
/// @param deltaTime Tiempo entre frames.
/// @param map Referencia al mapa.
void Projectile::Update(float deltaTime, CommandQueue& queue) {
    // Movimiento
    float newX = posX + dirX * speed * deltaTime;
    float newY = posY + dirY * speed * deltaTime;

    // Comprobaci�n simple de colisi�n con el mapa
    SDL_Rect futureRect = {
        static_cast<int>(newX),
        static_cast<int>(newY),
        hitbox.w,
        hitbox.h
    };

    // Obtenci�n de tiles ocupados
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

    // Movimiento si no hay colisi�n
    posX = newX;
    posY = newY;

    // Actualizaci�n del tiempo de vida
    lifetime += deltaTime;
    if (lifetime >= maxLifetime) {
        isActive = false;
    }*/
}

/// @brief Renderiza el proyectil como un rect�ngulo blanco.
/// @param renderer Renderer SDL.
/// @param cameraViewport Viewport/c�mara actual.
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
