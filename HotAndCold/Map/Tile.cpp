#include "Tile.h"
#include <SDL.h>

/// @brief Constructor de Tile.
/// @param typeID ID de tipo de tile (agua, muro, césped, etc.).
/// @param texture Textura compartida del tileset.
/// @param srcRect Rectángulo dentro del tileset que representa este tile.
/// @param solid Si el tile es sólido (colisiona).
Tile::Tile(int typeID, SDL_Texture* texture, const SDL_Rect& srcRect, bool solid)
    : typeID(typeID), texture(texture), srcRect(srcRect), solid(solid) {
    // Constructor simple, todos los valores se inicializan en la lista de inicialización.
}

/// @brief Renderiza el tile en la posición de pantalla recibida.
/// @param renderer Renderer SDL.
/// @param screenX Posición X en pantalla.
/// @param screenY Posición Y en pantalla.
void Tile::Render(SDL_Renderer* renderer, int screenX, int screenY) const {
    // Definir el área destino donde se dibujará el tile en pantalla.
    SDL_Rect destRect = { screenX, screenY, srcRect.w, srcRect.h };

    // Renderiza usando el srcRect dentro del tileset hacia destRect en pantalla.
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
