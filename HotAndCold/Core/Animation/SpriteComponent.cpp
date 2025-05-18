#include "SpriteComponent.h"

/**
 * @brief Constructor. Inicializa con una textura y una máquina de estados de animación.
 */
SpriteComponent::SpriteComponent(SDL_Texture* texture, std::shared_ptr<AnimationStateMachine> animationMachine)
    : texture(texture), stateMachine(animationMachine) {
}

/**
 * @brief Renderiza el sprite usando el frame actual de la animación.
 *
 * @param renderer Renderer SDL donde se dibuja.
 * @param position Rectángulo de destino en pantalla.
 */
void SpriteComponent::Render(SDL_Renderer* renderer, const SDL_Rect& position) {
    if (!texture || !stateMachine) return;

    // Obtener el frame actual de la animación
    const SDL_Rect& srcRect = stateMachine->GetCurrentFrame();

    // Renderiza el frame desde la textura al destino
    SDL_RenderCopy(renderer, texture, &srcRect, &position);
}

/**
 * @brief Devuelve una referencia compartida a la máquina de animación.
 */
std::shared_ptr<AnimationStateMachine> SpriteComponent::GetStateMachine() {
    return stateMachine;
}

/**
 * @brief Cambia la textura usada por el sprite.
 */
void SpriteComponent::SetTexture(SDL_Texture* newTexture) {
    texture = newTexture;
}
