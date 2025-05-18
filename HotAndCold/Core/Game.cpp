#include "Game.h"
#include "../Map/TileMap.h"
#include "../Map/Tile.h"
#include "../Map/WorldLoader.h"
#include "../Map/IWorld.h"
#include "../Entities/Player.h"
#include "../Managers/InputManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/Commands/CommandQueue.h"
#include "../Core/Camera/Camera.h"
#include "../Core/Config.h"
#include <iostream>

// Instancias globales locales (en el futuro serían singletons o sistemas internos)
EntityManager* entityManager = nullptr;
CommandQueue commandQueue;
Player* player = nullptr;
WorldLoader* worldLoader = nullptr;
IWorld* logicWorld = nullptr;
TileMap* renderTileMap = nullptr;
Camera* camera = nullptr;

SDL_Texture* testTexture = nullptr;
SDL_Texture* greenTexture = nullptr;
SDL_Texture* blueTexture = nullptr;
SDL_Texture* grayTexture = nullptr;
Tile* testTile = nullptr;
Tile* greenTile = nullptr;
Tile* blueTile = nullptr;
Tile* grayTile = nullptr;

/// @brief Constructor del juego. Inicializa variables.
Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(false) {
}

/// @brief Destructor del juego. Libera recursos.
Game::~Game() {
    Clean();
}

/// @brief Crea una textura simple de test.
/// @param renderer Renderer de SDL.
/// @param color Color de la textura.
/// @param tileSize Tamaño en píxeles.
/// @return Textura generada.
SDL_Texture* Game::CreateTestTile(SDL_Renderer* renderer, SDL_Color color, int tileSize) {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, tileSize, tileSize, 32,
        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

/// @brief Inicializa SDL, la ventana, el renderer y los sistemas básicos.
/// @return true si inicialización fue correcta.
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

    logicWorld = WorldLoader::CreateTestWorld(renderer);
    renderTileMap = dynamic_cast<TileMap*>(logicWorld);

    // EntityManager y Player
    entityManager = new EntityManager();
    player = new Player(logicWorld->GetWidth() * logicWorld->GetTileSize() / 2,
        logicWorld->GetHeight() * logicWorld->GetTileSize() / 2);
    entityManager->Add(std::unique_ptr<Entity>(player));

    // Configurar cámara y límites
    camera = new Camera(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
    SDL_Rect mapBounds = { 0, 0, logicWorld->GetWidth() * logicWorld->GetTileSize(), logicWorld->GetHeight() * logicWorld->GetTileSize() };
    camera->SetLimits(mapBounds);
    camera->UpdateViewportFromWindow(window);
    camera->RecalculateDeadZone(0.15f);
    camera->SetTarget(player);

    InputManager::Init();

    isRunning = true;
    std::cout << "[Game] Initialized successfully." << std::endl;
    return true;
}

/// @brief Procesa eventos SDL (teclado, ratón, etc.).
void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
            std::cout << "[Game] Quit event received." << std::endl;
        }
        InputManager::ProcessEvent(event);
    }

}

/// @brief Actualiza el juego completo (input, entidades, cámara).
void Game::Update() {
    static Uint32 lastTicks = SDL_GetTicks();
    Uint32 currentTicks = SDL_GetTicks();
    float deltaTime = (currentTicks - lastTicks) / 1000.0f;
    lastTicks = currentTicks;

    InputManager::Update();

    if (entityManager) {
        entityManager->Update(deltaTime, *logicWorld, commandQueue);
    }

    // Procesar todos los comandos acumulados (como spawns)
    commandQueue.Process(*entityManager);

    if (camera) {
        camera->Update(window);
    }
}

/// @brief Renderiza toda la escena.
void Game::Render() {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    if (renderTileMap) {
        renderTileMap->Render(renderer, camera->GetViewport());
    }

    if (entityManager) {
        entityManager->Render(renderer, camera->GetViewport());
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    for (int x = 0; x < windowWidth; x += 32)
        SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
    for (int y = 0; y < windowHeight; y += 32)
        SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);

    SDL_RenderPresent(renderer);
}

/// @brief Libera todos los recursos y cierra SDL.
void Game::Clean() {
    if (logicWorld) { 
        delete logicWorld; 
        logicWorld = nullptr;
		renderTileMap = nullptr;
    }
    if (camera) { delete camera; camera = nullptr; }
    if (entityManager) { delete entityManager; entityManager = nullptr; }

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

/// @brief Devuelve si el juego sigue activo.
/// @return true si el juego está en ejecución.
bool Game::Running() const {
    return isRunning;
}
