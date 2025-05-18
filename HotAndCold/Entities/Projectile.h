#pragma once

#include "Entity.h"

/// @brief Representa proyectiles simples (flechas, balas, hechizos...).
/// No tiene vida ni facción.
/// Se mueve en línea recta y se destruye al colisionar o tras un tiempo máximo.
class Projectile : public Entity {
public:
    /// @brief Constructor.
    /// @param x Posición X inicial.
    /// @param y Posición Y inicial.
    /// @param dirX Dirección X normalizada.
    /// @param dirY Dirección Y normalizada.
    /// @param speed Velocidad en píxeles por segundo.
    /// @param maxLifetime Tiempo máximo de vida en segundos.
    Projectile(float x, float y, float dirX, float dirY, float speed, float maxLifetime);

    /// @brief Actualiza el proyectil (movimiento, colisión, vida).
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al TileMap.
    void Update(float deltaTime, CommandQueue& queue) override;

    /// @brief Renderiza el proyectil.
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/cámara actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) override;

private:
    float dirX;
    float dirY;
    float speed;
    float lifetime = 0.0f;
    float maxLifetime;
};
