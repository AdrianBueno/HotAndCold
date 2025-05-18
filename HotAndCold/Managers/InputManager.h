#pragma once

#include <SDL.h>
#include <unordered_map>
#include <string>

/// @brief Sistema centralizado de entrada.
/// Se encarga de mapear teclas físicas a acciones abstractas (ej: "MoveLeft").
/// Permite desacoplar input físico de lógica de entidades.
class InputManager {
public:
    /// @brief Inicializa el InputManager.
    static void Init();

    /// @brief Procesa los eventos SDL y actualiza el estado interno.
    /// @param event Evento SDL.
    static void ProcessEvent(const SDL_Event& event);

    /// @brief Actualiza el estado de las teclas (debe llamarse una vez por frame).
    static void Update();

    /// @brief Comprueba si una acción está actualmente presionada.
    /// @param action Nombre de la acción (ej: "MoveLeft").
    /// @return true si la acción está activa.
    static bool IsActionPressed(const std::string& action);

    /// @brief Permite mapear una acción a una tecla SDL.
    /// @param action Nombre de la acción.
    /// @param key SDL_Scancode de la tecla.
    static void BindAction(const std::string& action, SDL_Scancode key);

private:
    static std::unordered_map<std::string, SDL_Scancode> actionBindings;
    static const Uint8* keyboardState;
};
