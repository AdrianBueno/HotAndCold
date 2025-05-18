#include "StaticEntity.h"
#include <SDL.h>

/// @brief Constructor de StaticEntity.
/// @param x Posici�n X inicial.
/// @param y Posici�n Y inicial.
/// @param width Ancho del hitbox.
/// @param height Alto del hitbox.
StaticEntity::StaticEntity(float x, float y, int width, int height)
    : Entity(x, y) {
    // Definimos el hitbox seg�n par�metros
    hitbox = { 0, 0, width, height };
}

/// @brief Actualizaci�n de StaticEntity.
/// Por defecto no hace nada, ya que es est�tico.
/// @param deltaTime Tiempo entre frames.
/// @param map Referencia al TileMap.
void StaticEntity::Update(float deltaTime, CommandQueue& queue) {
    // Entidades est�ticas no tienen l�gica de update por defecto.
}

/// @brief Renderiza la StaticEntity como un bloque gris.
/// @param renderer Renderer SDL.
/// @param cameraViewport Viewport/c�mara actual.
void StaticEntity::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) {
    SDL_Rect screenRect = {
        static_cast<int>(posX) - cameraViewport.x,
        static_cast<int>(posY) - cameraViewport.y,
        hitbox.w,
        hitbox.h
    };

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gris oscuro para objetos est�ticos
    SDL_RenderFillRect(renderer, &screenRect);
}
