#include "WorldLoader.h"
#include "TileMap.h"
#include "Tile.h"
#include <iostream>

IWorld* WorldLoader::CreateTestWorld(SDL_Renderer* renderer) {
    const int tileSize = 32;
    const int mapWidth = 100;
    const int mapHeight = 100;

    // Crear TileMap
    TileMap* tileMap = new TileMap(mapWidth, mapHeight, tileSize);

    // Crear texturas de test
    SDL_Texture* testTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tileSize, tileSize);
    SDL_Texture* greenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tileSize, tileSize);
    SDL_Texture* blueTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tileSize, tileSize);
    SDL_Texture* grayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tileSize, tileSize);

    // Función auxiliar para rellenar textura con color
    auto FillTexture = [&](SDL_Texture* texture, SDL_Color color) {
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
        };

    FillTexture(testTexture, { 255, 0, 0, 255 });
    FillTexture(greenTexture, { 0, 255, 0, 255 });
    FillTexture(blueTexture, { 0, 0, 255, 255 });
    FillTexture(grayTexture, { 128, 128, 128, 255 });

    // Crear tiles
    Tile* testTile = new Tile(1, testTexture, { 0, 0, tileSize, tileSize }, false);
    Tile* greenTile = new Tile(2, greenTexture, { 0, 0, tileSize, tileSize }, false);
    Tile* blueTile = new Tile(3, blueTexture, { 0, 0, tileSize, tileSize }, false);
    Tile* grayTile = new Tile(4, grayTexture, { 0, 0, tileSize, tileSize }, false);

    // Rellenar el mapa con diferentes zonas de colores
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (x > 20 && x < 40 && y > 20 && y < 40)
                tileMap->SetTile(TileMap::LAYER_GROUND, x, y, greenTile);
            else if (x > 50 && x < 70 && y > 50 && y < 70)
                tileMap->SetTile(TileMap::LAYER_GROUND, x, y, blueTile);
            else if (x > 10 && x < 15 && y > 60 && y < 80)
                tileMap->SetTile(TileMap::LAYER_GROUND, x, y, grayTile);
            else
                tileMap->SetTile(TileMap::LAYER_GROUND, x, y, testTile);
        }
    }

    // IMPORTANTE:
    // Aquí podrías almacenar los Tile* en un pool centralizado para liberar memoria adecuadamente si fuera necesario

    return tileMap;
}
