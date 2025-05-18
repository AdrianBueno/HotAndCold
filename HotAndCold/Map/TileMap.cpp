#include "TileMap.h"
#include <iostream>

/// @brief Constructor de TileMap.
/// @param mapWidth Ancho del mapa en tiles.
/// @param mapHeight Alto del mapa en tiles.
/// @param tileSize Tamaño de cada tile en píxeles.
TileMap::TileMap(int mapWidth, int mapHeight, int tileSize)
    : mapWidth(mapWidth), mapHeight(mapHeight), tileSize(tileSize) {

    // Inicializamos cada capa con una matriz de tamaño [mapWidth * mapHeight], inicializada a nullptr
    layers.resize(LAYER_COUNT);

    for (int layer = 0; layer < LAYER_COUNT; ++layer) {
        layers[layer].resize(mapWidth * mapHeight, nullptr);
    }

    std::cout << "[TileMap] Initialized with " << LAYER_COUNT << " layers, size "
        << mapWidth << "x" << mapHeight << std::endl;
}

/// @brief Destructor.
TileMap::~TileMap() {
    // No eliminamos los Tile*, ya que son compartidos (Flyweight).
    layers.clear();
}

/// @brief Asigna un tile a una posición y capa.
/// @param layer Capa donde colocar el tile.
/// @param x Coordenada X en tiles.
/// @param y Coordenada Y en tiles.
/// @param tile Puntero al tile a asignar.
void TileMap::SetTile(LayerType layer, int x, int y, Tile* tile) {
    if (layer >= LAYER_COUNT || x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) {
        std::cerr << "[TileMap] SetTile: Invalid position or layer." << std::endl;
        return;
    }

    layers[layer][y * mapWidth + x] = tile;
}

/// @brief Obtiene el tile en una posición y capa.
/// @param layer Capa a consultar.
/// @param x Coordenada X en tiles.
/// @param y Coordenada Y en tiles.
/// @return Puntero al tile o nullptr si vacío.
Tile* TileMap::GetTile(LayerType layer, int x, int y) const {
    if (layer >= LAYER_COUNT || x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) {
        return nullptr;
    }

    return layers[layer][y * mapWidth + x];
}

/// @brief Renderiza todas las capas dentro del viewport.
/// @param renderer Renderer SDL.
/// @param cameraViewport Viewport que define el área visible en pantalla.
void TileMap::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) const {
    // Calcula qué tiles entran en el viewport
    int startX = cameraViewport.x / tileSize;
    int startY = cameraViewport.y / tileSize;
    int endX = (cameraViewport.x + cameraViewport.w) / tileSize + 1;
    int endY = (cameraViewport.y + cameraViewport.h) / tileSize + 1;

    // Asegura que no nos salgamos del mapa
    startX = std::max(0, startX);
    startY = std::max(0, startY);
    endX = std::min(mapWidth, endX);
    endY = std::min(mapHeight, endY);

    // Recorre todas las capas y renderiza en orden
    for (int layer = 0; layer < LAYER_COUNT; ++layer) {
        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                Tile* tile = layers[layer][y * mapWidth + x];
                if (tile) {
                    // Calcula la posición en pantalla relativa al viewport
                    int screenX = x * tileSize - cameraViewport.x;
                    int screenY = y * tileSize - cameraViewport.y;
                    tile->Render(renderer, screenX, screenY);
                }
            }
        }
    }
}


bool TileMap::IsSolidAt( int x, int y) const {
	return this->IsSolidAt(LAYER_COLLISION, x, y);
}

bool TileMap::IsSolidAt(LayerType layer, int x, int y) const {
    if (layer >= LAYER_COUNT || x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) {
        return false;
    }

    Tile* tile = layers[layer][y * mapWidth + x];
    if (tile) {
        return tile->IsSolid();
    }

    return false;
}
