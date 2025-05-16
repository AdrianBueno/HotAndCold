#include "Tile.h"
#include <SDL.h>

/// @brief Constructor de Tile.
/// @param typeID ID de tipo de tile (agua, muro, c�sped, etc.).
/// @param texture Textura compartida del tileset.
/// @param srcRect Rect�ngulo dentro del tileset que representa este tile.
/// @param solid Si el tile es s�lido (colisiona).
Tile::Tile(int typeID, SDL_Texture* texture, const SDL_Rect& srcRect, bool solid)
    : typeID(typeID), texture(texture), srcRect(srcRect), solid(solid) {
    // Constructor simple, todos los valores se inicializan en la lista de inicializaci�n.
}

/// @brief Renderiza el tile en la posici�n de pantalla recibida.
/// @param renderer Renderer SDL.
/// @param screenX Posici�n X en pantalla.
/// @param screenY Posici�n Y en pantalla.
void Tile::Render(SDL_Renderer* renderer, int screenX, int screenY) const {
    // Definir el �rea destino donde se dibujar� el tile en pantalla.
    SDL_Rect destRect = { screenX, screenY, srcRect.w, srcRect.h };

    // Renderiza usando el srcRect dentro del tileset hacia destRect en pantalla.
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
