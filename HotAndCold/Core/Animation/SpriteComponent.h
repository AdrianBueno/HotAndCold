#pragma once

#include <SDL.h>
#include <string>
#include <memory>
#include "AnimationStateMachine.h"

/**
 * @brief Componente encargado de renderizar el sprite animado de una entidad.
 *
 * Usa una textura compartida y una máquina de estados de animación para determinar
 * qué parte del sprite sheet debe dibujarse.
 */
class SpriteComponent {
public:
    /**
     * @brief Constructor del SpriteComponent.
     * @param texture Textura del sprite sheet compartida.
     * @param animationMachine Máquina de estados de animación asociada.
     */
    SpriteComponent(SDL_Texture* texture, std::shared_ptr<AnimationStateMachine> animationMachine);

    /**
     * @brief Renderiza el sprite animado en pantalla.
     * @param renderer Renderer SDL2.
     * @param position Posición en el mundo (ej. obtenida del componente de transformación).
     */
    void Render(SDL_Renderer* renderer, const SDL_Rect& position);

    /**
     * @brief Accede a la máquina de estados para poder modificarla desde el exterior.
     */
    std::shared_ptr<AnimationStateMachine> GetStateMachine();

    /**
     * @brief Cambia la textura del componente (útil para cambiar de skin).
     */
    void SetTexture(SDL_Texture* newTexture);

private:
    SDL_Texture* texture; ///< Textura del sprite sheet
    std::shared_ptr<AnimationStateMachine> stateMachine; ///< Máquina de animación activa
};
