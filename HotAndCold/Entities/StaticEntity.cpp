#include "StaticEntity.h"
#include <SDL.h>

/// @brief Constructor de StaticEntity.
/// @param x Posición X inicial.
/// @param y Posición Y inicial.
/// @param width Ancho del hitbox.
/// @param height Alto del hitbox.
StaticEntity::StaticEntity(float x, float y, int width, int height)
    : Entity(x, y) {
    // Definimos el hitbox según parámetros
    hitbox = { 0, 0, width, height };
}

/// @brief Actualización de StaticEntity.
/// Por defecto no hace nada, ya que es estático.
/// @param deltaTime Tiempo entre frames.
/// @param map Referencia al TileMap.
void StaticEntity::Update(float deltaTime, CommandQueue& queue) {
    // Entidades estáticas no tienen lógica de update por defecto.
}

/// @brief Renderiza la StaticEntity como un bloque gris.
/// @param renderer Renderer SDL.
/// @param cameraViewport Viewport/cámara actual.
void StaticEntity::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) {
    SDL_Rect screenRect = {
        static_cast<int>(posX) - cameraViewport.x,
        static_cast<int>(posY) - cameraViewport.y,
        hitbox.w,
        hitbox.h
    };

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gris oscuro para objetos estáticos
    SDL_RenderFillRect(renderer, &screenRect);
}
