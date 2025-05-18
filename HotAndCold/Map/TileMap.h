#pragma once

#include "Tile.h"
#include <SDL.h>
#include <vector>
#include "IWorld.h"

/// @brief Representa el mapa completo con m�ltiples capas de tiles.
class TileMap : public IWorld {
public:
    /// @brief Capas l�gicas del mapa. Se recomienda seguir este orden para facilitar el render.
/// Puedes agregar nuevas capas en el futuro sin afectar el c�digo existente, siempre manteniendo LAYER_COUNT al final.
    enum LayerType {
        /// Capa de fondo principal. Normalmente suelo, agua, caminos.
        LAYER_GROUND = 0, //A partir de aqu� incrementan a partir de 0.
        /// Capa de elementos s�lidos que bloquean el paso. Muros, rocas.
        LAYER_COLLISION,
        /// Capa de decoraci�n por encima del terreno (arbustos, decorados visuales).
        LAYER_DECORATION,
        /// Capa de elementos de overlay, efectos gr�ficos (nubes, sombras, efectos de clima).
        LAYER_OVERLAY,
        /// Capa reservada para datos de sistema, triggers, spawn points, zonas ocultas. No se renderiza.
        LAYER_SYSTEM,
        /// Contador autom�tico de capas. Mantener siempre al final.
        LAYER_COUNT
    };

    /// @brief Constructor.
    /// @param mapWidth Ancho del mapa en tiles.
    /// @param mapHeight Alto del mapa en tiles.
    /// @param tileSize Tama�o de cada tile en p�xeles.
    TileMap(int mapWidth, int mapHeight, int tileSize);

    /// @brief Destructor.
    ~TileMap();

    /// @brief Renderiza el mapa dentro del viewport.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) const;

    /// @brief Asigna un tile a una posici�n en una capa espec�fica.
    void SetTile(LayerType layer, int x, int y, Tile* tile);

    /// @brief Obtiene el tile en una capa y posici�n espec�fica.
    Tile* GetTile(LayerType layer, int x, int y) const;

    /// @brief Getters varios.
    int GetNumLayers() const { return static_cast<int>(LAYER_COUNT); }
    int GetWidth() const { return mapWidth; }
    int GetHeight() const { return mapHeight; }
    /// @brief Devuelve el tama�o de tile en p�xeles definido para este mapa.
    /// @return Tama�o del tile en p�xeles.
    int GetTileSize() const { return tileSize; }


	/// @brief M�todo para comprobar si un tile es s�lido en una capa y posici�n espec�fica.
    /// @param layer La capa a consultar.
    /// @param x Posici�n horizontal del tile en el mapa.
    /// @param y Posici�n vertical del tile en el mapa.
    /// <returns>bool </returns>
    bool IsSolidAt( int x, int y) const;
    


    

private:
    int mapWidth;
    int mapHeight;
    int tileSize;

    // Cada capa es una matriz lineal (vector de Tile*), las capas se almacenan en un vector de capas.
    std::vector<std::vector<Tile*>> layers;
    bool IsSolidAt(LayerType layer, int x, int y) const;
};
