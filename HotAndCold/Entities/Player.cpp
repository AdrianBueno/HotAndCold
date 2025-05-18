#include "Player.h"
#include <SDL.h>
#include "../Managers/InputManager.h"
#include "../Managers/Commands/CommandSpawnProjectile.h"


/// @brief Constructor de Player.
/// @param x Posición X inicial.
/// @param y Posición Y inicial.
Player::Player(float x, float y)
    : Entity(x, y) {
    // Definimos el hitbox estándar (puede ser ajustado según el sprite real)
    hitbox = { 0, 0, 28, 28 }; // Por defecto 28x28 píxeles relativo a posX, posY
}

/// @brief Actualiza el jugador.
/// Actualmente sin lógica interna.
/// El movimiento es gestionado desde Game.
/// @param deltaTime Tiempo entre frames.
/// @param map Referencia al TileMap.
void Player::Update(float deltaTime, CommandQueue& queue) {
    this->HandleInput(queue);
    // Aquí podrías añadir futuras animaciones, IA, efectos, etc.
    
}

/// @brief Renderiza el jugador en pantalla.
/// @param renderer Renderer de SDL.
/// @param cameraViewport Viewport/cámara actual.
void Player::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) {
    // Calcula la posición relativa a la cámara
    SDL_Rect screenRect = {
        static_cast<int>(posX) - cameraViewport.x,
        static_cast<int>(posY) - cameraViewport.y,
        hitbox.w,
        hitbox.h
    };

    // Renderiza el rectángulo amarillo representando al jugador
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &screenRect);
}






/// @brief Gestiona el input del jugador utilizando acciones abstractas del InputManager.
/// Traduce las acciones a movimiento, verifica colisión antes de aplicar el desplazamiento.
/// Esto permite desacoplar la entrada física del movimiento y preparar el sistema para multientidad o IA.
/// @param map Referencia al TileMap para comprobar colisiones.
void Player::HandleInput(CommandQueue& commandQueue) {
    // Capturamos la posición actual
    float newX = GetX();
    float newY = GetY();

    // Calculamos desplazamiento teniendo en cuenta la velocidad y deltaTime (por ahora fijo a 60 FPS)
    float move = GetSpeed() * 0.016f;

    // Comprobamos acciones abstractas definidas en InputManager
    if (InputManager::IsActionPressed("MoveLeft")) newX -= move;
    if (InputManager::IsActionPressed("MoveRight")) newX += move;
    if (InputManager::IsActionPressed("MoveUp")) newY -= move;
    if (InputManager::IsActionPressed("MoveDown")) newY += move;

    this->SetX(newX);
    this->SetY(newY);
  

    if (InputManager::IsActionPressed("Shoot")) {
        commandQueue.Enqueue(std::make_unique<CommandSpawnProjectile>(posX, posY, 1.0f, 0.0f, 400.0f, 2.0f));
    }

    if (InputManager::IsActionPressed("Jump")) {
        // Preparado, aún sin lógica real
    }
}




