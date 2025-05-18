#pragma once

#include "Entity.h"

/// @brief Representa proyectiles simples (flechas, balas, hechizos...).
/// No tiene vida ni facci�n.
/// Se mueve en l�nea recta y se destruye al colisionar o tras un tiempo m�ximo.
class Projectile : public Entity {
public:
    /// @brief Constructor.
    /// @param x Posici�n X inicial.
    /// @param y Posici�n Y inicial.
    /// @param dirX Direcci�n X normalizada.
    /// @param dirY Direcci�n Y normalizada.
    /// @param speed Velocidad en p�xeles por segundo.
    /// @param maxLifetime Tiempo m�ximo de vida en segundos.
    Projectile(float x, float y, float dirX, float dirY, float speed, float maxLifetime);

    /// @brief Actualiza el proyectil (movimiento, colisi�n, vida).
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al TileMap.
    void Update(float deltaTime, CommandQueue& queue) override;

    /// @brief Renderiza el proyectil.
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/c�mara actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) override;

private:
    float dirX;
    float dirY;
    float speed;
    float lifetime = 0.0f;
    float maxLifetime;
};
