#include "SpriteComponent.h"

/**
 * @brief Constructor. Inicializa con una textura y una m�quina de estados de animaci�n.
 */
SpriteComponent::SpriteComponent(SDL_Texture* texture, std::shared_ptr<AnimationStateMachine> animationMachine)
    : texture(texture), stateMachine(animationMachine) {
}

/**
 * @brief Renderiza el sprite usando el frame actual de la animaci�n.
 *
 * @param renderer Renderer SDL donde se dibuja.
 * @param position Rect�ngulo de destino en pantalla.
 */
void SpriteComponent::Render(SDL_Renderer* renderer, const SDL_Rect& position) {
    if (!texture || !stateMachine) return;

    // Obtener el frame actual de la animaci�n
    const SDL_Rect& srcRect = stateMachine->GetCurrentFrame();

    // Renderiza el frame desde la textura al destino
    SDL_RenderCopy(renderer, texture, &srcRect, &position);
}

/**
 * @brief Devuelve una referencia compartida a la m�quina de animaci�n.
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
