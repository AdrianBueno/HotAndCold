#pragma once

#include "Tile.h"
#include <SDL.h>
#include <vector>

/// @brief Representa el mapa completo con múltiples capas de tiles.
class TileMap {
public:
    /// @brief Capas lógicas del mapa. Se recomienda seguir este orden para facilitar el render.
/// Puedes agregar nuevas capas en el futuro sin afectar el código existente, siempre manteniendo LAYER_COUNT al final.
    enum LayerType {
        /// Capa de fondo principal. Normalmente suelo, agua, caminos.
        LAYER_GROUND = 0, //A partir de aquí incrementan a partir de 0.
        /// Capa de elementos sólidos que bloquean el paso. Muros, rocas.
        LAYER_COLLISION,
        /// Capa de decoración por encima del terreno (arbustos, decorados visuales).
        LAYER_DECORATION,
        /// Capa de elementos de overlay, efectos gráficos (nubes, sombras, efectos de clima).
        LAYER_OVERLAY,
        /// Capa reservada para datos de sistema, triggers, spawn points, zonas ocultas. No se renderiza.
        LAYER_SYSTEM,
        /// Contador automático de capas. Mantener siempre al final.
        LAYER_COUNT
    };

    /// @brief Constructor.
    /// @param mapWidth Ancho del mapa en tiles.
    /// @param mapHeight Alto del mapa en tiles.
    /// @param tileSize Tamaño de cada tile en píxeles.
    TileMap(int mapWidth, int mapHeight, int tileSize);

    /// @brief Destructor.
    ~TileMap();

    /// @brief Renderiza el mapa dentro del viewport.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) const;

    /// @brief Asigna un tile a una posición en una capa específica.
    void SetTile(LayerType layer, int x, int y, Tile* tile);

    /// @brief Obtiene el tile en una capa y posición específica.
    Tile* GetTile(LayerType layer, int x, int y) const;

    /// @brief Getters varios.
    int GetNumLayers() const { return static_cast<int>(LAYER_COUNT); }
    int GetWidth() const { return mapWidth; }
    int GetHeight() const { return mapHeight; }

private:
    int mapWidth;
    int mapHeight;
    int tileSize;

    // Cada capa es una matriz lineal (vector de Tile*), las capas se almacenan en un vector de capas.
    std::vector<std::vector<Tile*>> layers;
};
