#pragma once

#include "Entity.h"

/// @brief Representa entidades estáticas del mundo (rocas, cofres, árboles, puertas...).
/// No tienen vida, no se mueven.
/// Pueden opcionalmente tener interacción (se añadiría luego con un componente o flag).
class StaticEntity : public Entity {
public:
    /// @brief Constructor.
    /// @param x Posición X inicial.
    /// @param y Posición Y inicial.
    /// @param width Ancho del hitbox.
    /// @param height Alto del hitbox.
    StaticEntity(float x, float y, int width, int height);

    /// @brief Actualiza la entidad estática (por defecto no hace nada).
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al mapa.
    void Update(float deltaTime, CommandQueue& queue) override;

    /// @brief Renderiza la entidad estática.
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/cámara actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) override;
};
