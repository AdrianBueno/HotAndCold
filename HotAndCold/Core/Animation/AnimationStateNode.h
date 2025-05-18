#pragma once

#include <string>
#include <vector>
#include <functional>
#include "Animation.h"

/**
 * @brief Representa una transición entre dos estados de animación.
 *
 * Contiene una condición que, si se cumple, activa el cambio de estado.
 */
struct AnimationTransition {
    std::string targetState; ///< Nombre del estado destino
    std::function<bool()> condition; ///< Función de condición evaluada en tiempo de ejecución
};

/**
 * @brief Nodo que representa un estado de animación dentro de la máquina de estados.
 */
struct AnimationStateNode {
    std::string name; ///< Identificador del estado (ej. "Idle", "Walk")
    std::shared_ptr<Animation> animation; ///< Animación compartida
    std::vector<AnimationTransition> transitions; ///< Transiciones salientes desde este estado

    /**
     * @brief Constructor rápido para definir un estado por nombre y animación.
     */
    AnimationStateNode(const std::string& stateName, std::shared_ptr<Animation> anim)
        : name(stateName), animation(anim) {
    }
};
