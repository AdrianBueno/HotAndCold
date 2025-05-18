#include "Actor.h"
#include <SDL.h>
#include <iostream>

/// @brief Constructor del actor genérico.
/// @param x Posición X inicial.
/// @param y Posición Y inicial.
Actor::Actor(float x, float y)
    : Entity(x, y) {
    // Ajuste de hitbox estándar (puedes personalizar por entidad)
    hitbox = { 0, 0, 32, 32 };
}

/// @brief Actualiza el actor.
/// Por defecto no hace nada.
/// Las clases hijas pueden sobreescribir este método si necesitan lógica personalizada.
/// @param deltaTime Tiempo entre frames.
/// @param map Referencia al mapa.
void Actor::Update(float deltaTime, CommandQueue& queue) {
    // Actor genérico no tiene comportamiento por defecto.
    // Las clases derivadas pueden implementar IA, navegación, etc.
}

/// @brief Renderiza el actor como un rectángulo rojo.
/// Las clases derivadas pueden sobreescribir para añadir sprites.
/// @param renderer Renderer SDL.
/// @param cameraViewport Viewport/cámara actual.
void Actor::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) {
    SDL_Rect screenRect = {
        static_cast<int>(posX) - cameraViewport.x,
        static_cast<int>(posY) - cameraViewport.y,
        hitbox.w,
        hitbox.h
    };

    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); // Rojo estándar para actores genéricos
    SDL_RenderFillRect(renderer, &screenRect);
}

/// @brief Recibe daño. Si la salud llega a 0, la entidad es desactivada.
/// @param amount Cantidad de daño recibido.
void Actor::TakeDamage(int amount) {
    health -= amount;
    std::cout << "[Actor] Recibido " << amount << " de daño. Vida restante: " << health << std::endl;
    if (health <= 0) {
        isActive = false;
        std::cout << "[Actor] Actor muerto." << std::endl;
    }
}
