#pragma once

#include "Entity.h"
#include "Projectile.h"



/// @brief Clase Player. Hereda de Entity.
/// Gestiona movimiento, colisión y renderizado del jugador.
class Player : public Entity {
public:
    /// @brief Constructor.
    /// @param x Posición X inicial.
    /// @param y Posición Y inicial.
    Player(float x, float y);

    /// @brief Destructor.
    ~Player() override {}

    /// @brief Actualiza el jugador (animación, IA, comportamiento...).
    /// El movimiento es gestionado desde Game mediante input externo.
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al TileMap.
    void Update(float deltaTime, CommandQueue& queue) override;

    /// @brief Renderiza el jugador en pantalla.
    /// @param renderer Renderer de SDL.
    /// @param cameraViewport Viewport/cámara actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) override;

    /// @brief Devuelve la velocidad de movimiento actual del jugador.
    /// @return Velocidad en píxeles por segundo.
    float GetSpeed() const { return speed; }

    
    void HandleInput(CommandQueue& commandQueue);


private:
    float speed = 500.0f; ///< Velocidad de movimiento en píxeles por segundo.
};
