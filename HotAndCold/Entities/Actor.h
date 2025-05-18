#pragma once

#include "Entity.h"
#include <string>

/// @brief Clase base para cualquier entidad viva y dinámica del juego (jugadores, enemigos, NPC, animales, etc.).
/// Incluye vida, velocidad, gestión de daños y facciones.
/// El comportamiento (hostil, aliado, neutro) se determinará externamente mediante sistemas como FactionManager.
class Actor : public Entity {
public:
    /// @brief Constructor.
    /// @param x Posición X inicial.
    /// @param y Posición Y inicial.
    Actor(float x, float y);

    /// @brief Destructor.
    ~Actor() override {}

    /// @brief Actualiza la entidad (debe ser sobreescrito por clases derivadas si es necesario).
    /// Por defecto no hace nada.
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al mapa.
    void Update(float deltaTime, CommandQueue& queue) override;

    /// @brief Renderiza la entidad (cuadro genérico).
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/cámara actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) override;

    /// @brief Recibe daño.
    /// Si la vida baja a 0 o menos, la entidad es marcada como inactiva.
    /// @param amount Cantidad de daño recibido.
    virtual void TakeDamage(int amount);

    /// @brief Devuelve la salud actual.
    int GetHealth() const { return health; }

    /// @brief Devuelve la facción actual.
    const std::string& GetFaction() const { return faction; }

    /// @brief Cambia la facción.
    /// @param f Nueva facción.
    void SetFaction(const std::string& f) { faction = f; }

    /// @brief Devuelve la velocidad actual.
    float GetSpeed() const { return speed; }

protected:
    int health = 100;            ///< Salud actual.
    float speed = 100.0f;        ///< Velocidad de movimiento en píxeles por segundo.
    std::string faction = "Neutral"; ///< Facción inicial. Puede usarse con FactionManager.
};

