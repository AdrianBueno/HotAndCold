#include "Actor.h"
#include <SDL.h>
#include <iostream>

/// @brief Constructor del actor gen�rico.
/// @param x Posici�n X inicial.
/// @param y Posici�n Y inicial.
Actor::Actor(float x, float y)
    : Entity(x, y) {
    // Ajuste de hitbox est�ndar (puedes personalizar por entidad)
    hitbox = { 0, 0, 32, 32 };
}

/// @brief Actualiza el actor.
/// Por defecto no hace nada.
/// Las clases hijas pueden sobreescribir este m�todo si necesitan l�gica personalizada.
/// @param deltaTime Tiempo entre frames.
/// @param map Referencia al mapa.
void Actor::Update(float deltaTime, CommandQueue& queue) {
    // Actor gen�rico no tiene comportamiento por defecto.
    // Las clases derivadas pueden implementar IA, navegaci�n, etc.
}

/// @brief Renderiza el actor como un rect�ngulo rojo.
/// Las clases derivadas pueden sobreescribir para a�adir sprites.
/// @param renderer Renderer SDL.
/// @param cameraViewport Viewport/c�mara actual.
void Actor::Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) {
    SDL_Rect screenRect = {
        static_cast<int>(posX) - cameraViewport.x,
        static_cast<int>(posY) - cameraViewport.y,
        hitbox.w,
        hitbox.h
    };

    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); // Rojo est�ndar para actores gen�ricos
    SDL_RenderFillRect(renderer, &screenRect);
}

/// @brief Recibe da�o. Si la salud llega a 0, la entidad es desactivada.
/// @param amount Cantidad de da�o recibido.
void Actor::TakeDamage(int amount) {
    health -= amount;
    std::cout << "[Actor] Recibido " << amount << " de da�o. Vida restante: " << health << std::endl;
    if (health <= 0) {
        isActive = false;
        std::cout << "[Actor] Actor muerto." << std::endl;
    }
}
