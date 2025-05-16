#include "Game.h"
#include "../Map/TileMap.h"
#include "../Map/Tile.h"
#include <iostream>

// Variables internas añadidas
TileMap* tileMap = nullptr;
SDL_Texture* testTexture = nullptr;
SDL_Texture* greenTexture = nullptr;
SDL_Texture* blueTexture = nullptr;
SDL_Texture* grayTexture = nullptr;
Tile* testTile = nullptr;
Tile* greenTile = nullptr;
Tile* blueTile = nullptr;
Tile* grayTile = nullptr;
SDL_Rect cameraViewport = { 0, 0, 800, 600 }; // Vista inicial

/// @brief Constructor del juego. Inicializa punteros y estado base.
Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(false) {
}

/// @brief Destructor del juego. Limpia recursos de SDL.
Game::~Game() {
    Clean(); // Asegura que SDL se limpie correctamente al destruir el objeto
}

/// @brief Crea una textura simple de test.
SDL_Texture* Game::CreateTestTile(SDL_Renderer* renderer, SDL_Color color, int tileSize) {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, tileSize, tileSize, 32,
        0x00FF0000,
        0x0000FF00,
        0x000000FF,
        0xFF000000);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
/// @brief Inicializa SDL, crea ventana y renderer.
/// @param title Título de la ventana.
/// @param xpos Posición X de la ventana.
/// @param ypos Posición Y de la ventana.
/// @param width Ancho de la ventana.
/// @param height Alto de la ventana.
/// @param fullscreen Si es true, se crea en modo pantalla completa.
/// @return true si la inicialización fue exitosa, false en caso de error.
bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "[Game] SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    Uint32 windowFlags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    window = SDL_CreateWindow(title, xpos, ypos, width, height, windowFlags);
    if (!window) {
        std::cerr << "[Game] Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "[Game] Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    // Crear texturas y tiles de test de varios colores
    testTexture = CreateTestTile(renderer, { 255, 0, 0, 255 }, 32);
    greenTexture = CreateTestTile(renderer, { 0, 255, 0, 255 }, 32);
    blueTexture = CreateTestTile(renderer, { 0, 0, 255, 255 }, 32);
    grayTexture = CreateTestTile(renderer, { 128, 128, 128, 255 }, 32);

    testTile = new Tile(1, testTexture, { 0, 0, 32, 32 }, false);
    greenTile = new Tile(2, greenTexture, { 0, 0, 32, 32 }, false);
    blueTile = new Tile(3, blueTexture, { 0, 0, 32, 32 }, false);
    grayTile = new Tile(4, grayTexture, { 0, 0, 32, 32 }, false);

    // Crear el TileMap
    tileMap = new TileMap(100, 100, 32);
    for (int y = 0; y < tileMap->GetHeight(); ++y) {
        for (int x = 0; x < tileMap->GetWidth(); ++x) {
            // Crear zonas de colores
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

    isRunning = true;
    std::cout << "[Game] Initialized successfully." << std::endl;
    return true;
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
            std::cout << "[Game] Quit event received." << std::endl;
        }
    }

    // Movimiento cámara (teclas flechas)
    const int speed = 10;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) cameraViewport.x -= speed;
    if (state[SDL_SCANCODE_RIGHT]) cameraViewport.x += speed;
    if (state[SDL_SCANCODE_UP]) cameraViewport.y -= speed;
    if (state[SDL_SCANCODE_DOWN]) cameraViewport.y += speed;

    // Debug opcional
    // std::cout << "[Camera] Pos: " << cameraViewport.x << ", " << cameraViewport.y << std::endl;
}

void Game::Update() {
    // Aquí se actualizará la lógica del juego en el futuro (entidades, IA, física, etc.)
}

void Game::Render() {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Renderizar el TileMap
    if (tileMap) {
        tileMap->Render(renderer, cameraViewport);
    }

    // Dibujar rejilla de debug
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    for (int x = 0; x < 800; x += 32)
        SDL_RenderDrawLine(renderer, x, 0, x, 600);
    for (int y = 0; y < 600; y += 32)
        SDL_RenderDrawLine(renderer, 0, y, 800, y);

    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    if (tileMap) { delete tileMap; tileMap = nullptr; }

    if (testTile) { delete testTile; testTile = nullptr; }
    if (greenTile) { delete greenTile; greenTile = nullptr; }
    if (blueTile) { delete blueTile; blueTile = nullptr; }
    if (grayTile) { delete grayTile; grayTile = nullptr; }

    if (testTexture) { SDL_DestroyTexture(testTexture); testTexture = nullptr; }
    if (greenTexture) { SDL_DestroyTexture(greenTexture); greenTexture = nullptr; }
    if (blueTexture) { SDL_DestroyTexture(blueTexture); blueTexture = nullptr; }
    if (grayTexture) { SDL_DestroyTexture(grayTexture); grayTexture = nullptr; }

    if (renderer) { SDL_DestroyRenderer(renderer); renderer = nullptr; }
    if (window) { SDL_DestroyWindow(window); window = nullptr; }

    SDL_Quit();
    std::cout << "[Game] Cleaned and SDL Quit." << std::endl;
}

bool Game::Running() const {
    return isRunning;
}
