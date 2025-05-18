#pragma once

#include <string>
#include <vector>
#include <functional>
#include "Animation.h"

/**
 * @brief Representa una transici�n entre dos estados de animaci�n.
 *
 * Contiene una condici�n que, si se cumple, activa el cambio de estado.
 */
struct AnimationTransition {
    std::string targetState; ///< Nombre del estado destino
    std::function<bool()> condition; ///< Funci�n de condici�n evaluada en tiempo de ejecuci�n
};

/**
 * @brief Nodo que representa un estado de animaci�n dentro de la m�quina de estados.
 */
struct AnimationStateNode {
    std::string name; ///< Identificador del estado (ej. "Idle", "Walk")
    std::shared_ptr<Animation> animation; ///< Animaci�n compartida
    std::vector<AnimationTransition> transitions; ///< Transiciones salientes desde este estado

    /**
     * @brief Constructor r�pido para definir un estado por nombre y animaci�n.
     */
    AnimationStateNode(const std::string& stateName, std::shared_ptr<Animation> anim)
        : name(stateName), animation(anim) {
    }
};
