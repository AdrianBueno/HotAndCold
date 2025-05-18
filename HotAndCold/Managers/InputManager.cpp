#include "InputManager.h"

// Definición de miembros estáticos
std::unordered_map<std::string, SDL_Scancode> InputManager::actionBindings;
const Uint8* InputManager::keyboardState = nullptr;

/// @brief Inicializa el InputManager con bindings por defecto.
void InputManager::Init() {
    keyboardState = SDL_GetKeyboardState(NULL);

    // Bindings por defecto (puedes personalizarlos)
    BindAction("MoveLeft", SDL_SCANCODE_A);
    BindAction("MoveRight", SDL_SCANCODE_D);
    BindAction("MoveUp", SDL_SCANCODE_W);
    BindAction("MoveDown", SDL_SCANCODE_S);
    BindAction("Shoot", SDL_SCANCODE_E);
    BindAction("Jump", SDL_SCANCODE_SPACE);

}

/// @brief Procesa eventos SDL (por ahora vacío, se puede expandir para manejar mouse, gamepad, etc.).
void InputManager::ProcessEvent(const SDL_Event& event) {
    // Preparado para futuras extensiones (mouse, gamepad, etc.)
}

/// @brief Actualiza el estado interno (por ahora solo refresca el keyboardState).
void InputManager::Update() {
    keyboardState = SDL_GetKeyboardState(NULL);
}

/// @brief Comprueba si la acción está activa.
bool InputManager::IsActionPressed(const std::string& action) {
    auto it = actionBindings.find(action);
    if (it != actionBindings.end()) {
        return keyboardState[it->second];
    }
    return false;
}

/// @brief Asigna una acción a una tecla.
void InputManager::BindAction(const std::string& action, SDL_Scancode key) {
    actionBindings[action] = key;
}
