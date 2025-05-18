#pragma once

#include "Entity.h"

/// @brief Representa entidades est�ticas del mundo (rocas, cofres, �rboles, puertas...).
/// No tienen vida, no se mueven.
/// Pueden opcionalmente tener interacci�n (se a�adir�a luego con un componente o flag).
class StaticEntity : public Entity {
public:
    /// @brief Constructor.
    /// @param x Posici�n X inicial.
    /// @param y Posici�n Y inicial.
    /// @param width Ancho del hitbox.
    /// @param height Alto del hitbox.
    StaticEntity(float x, float y, int width, int height);

    /// @brief Actualiza la entidad est�tica (por defecto no hace nada).
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al mapa.
    void Update(float deltaTime, CommandQueue& queue) override;

    /// @brief Renderiza la entidad est�tica.
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/c�mara actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) override;
};
