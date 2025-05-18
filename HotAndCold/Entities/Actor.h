#pragma once

#include "Entity.h"
#include <string>

/// @brief Clase base para cualquier entidad viva y din�mica del juego (jugadores, enemigos, NPC, animales, etc.).
/// Incluye vida, velocidad, gesti�n de da�os y facciones.
/// El comportamiento (hostil, aliado, neutro) se determinar� externamente mediante sistemas como FactionManager.
class Actor : public Entity {
public:
    /// @brief Constructor.
    /// @param x Posici�n X inicial.
    /// @param y Posici�n Y inicial.
    Actor(float x, float y);

    /// @brief Destructor.
    ~Actor() override {}

    /// @brief Actualiza la entidad (debe ser sobreescrito por clases derivadas si es necesario).
    /// Por defecto no hace nada.
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al mapa.
    void Update(float deltaTime, CommandQueue& queue) override;

    /// @brief Renderiza la entidad (cuadro gen�rico).
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/c�mara actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) override;

    /// @brief Recibe da�o.
    /// Si la vida baja a 0 o menos, la entidad es marcada como inactiva.
    /// @param amount Cantidad de da�o recibido.
    virtual void TakeDamage(int amount);

    /// @brief Devuelve la salud actual.
    int GetHealth() const { return health; }

    /// @brief Devuelve la facci�n actual.
    const std::string& GetFaction() const { return faction; }

    /// @brief Cambia la facci�n.
    /// @param f Nueva facci�n.
    void SetFaction(const std::string& f) { faction = f; }

    /// @brief Devuelve la velocidad actual.
    float GetSpeed() const { return speed; }

protected:
    int health = 100;            ///< Salud actual.
    float speed = 100.0f;        ///< Velocidad de movimiento en p�xeles por segundo.
    std::string faction = "Neutral"; ///< Facci�n inicial. Puede usarse con FactionManager.
};

