#pragma once

#include <SDL.h>

/// @brief Representa la definición de un tipo de tile en el mapa (Flyweight).
///        Los tiles son compartidos y no contienen datos dinámicos.
///        Todo estado por celda debe gestionarse en el mapa o sistemas externos.
class Tile {
public:
    /// @brief Constructor.
    /// @param typeID Identificador de tipo de tile (ej: agua, tierra, muro).
    /// @param texture Textura asociada al tile.
    /// @param srcRect Área del tileset que representa el tile.
    /// @param solid Si el tile es sólido (colisiona).
    Tile(int typeID, SDL_Texture* texture, const SDL_Rect& srcRect, bool solid);

    /// @brief Renderiza el tile en una posición específica de pantalla.
    /// @param renderer Renderer de SDL.
    /// @param screenX Posición X en pantalla.
    /// @param screenY Posición Y en pantalla.
    void Render(SDL_Renderer* renderer, int screenX, int screenY) const;

    /// @brief Devuelve si el tile es sólido.
    bool IsSolid() const { return solid; }

    /// @brief Devuelve el ID del tipo de tile.
    int GetTypeID() const { return typeID; }

    /// @brief Devuelve la textura asociada.
    SDL_Texture* GetTexture() const { return texture; }

    /// @brief Devuelve el rectángulo fuente dentro del tileset.
    const SDL_Rect& GetSrcRect() const { return srcRect; }

private:
    int typeID;                    // Tipo de tile (agua, muro, césped, etc.)
    SDL_Texture* texture;          // Textura compartida por todos los tiles del mismo tipo
    SDL_Rect srcRect;              // Área dentro del tileset
    bool solid;                    // Si colisiona o no

    // 🚨 No almacena posición ni estado mutable
};
