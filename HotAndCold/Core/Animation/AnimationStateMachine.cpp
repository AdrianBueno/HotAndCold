#include "AnimationStateMachine.h"

/**
 * @brief Añade un nuevo estado con su animación.
 */
void AnimationStateMachine::AddState(const std::string& stateName, std::shared_ptr<Animation> animation) {
    states[stateName] = AnimationStateNode(stateName, animation);
}

/**
 * @brief Añade una transición desde un estado origen a un destino bajo cierta condición.
 */
void AnimationStateMachine::AddTransition(const std::string& from, const std::string& to, std::function<bool()> condition) {
    auto it = states.find(from);
    if (it != states.end()) {
        it->second.transitions.push_back(AnimationTransition{ to, condition });
    }
}

/**
 * @brief Cambia manualmente el estado actual y reinicia la animación.
 */
void AnimationStateMachine::SetState(const std::string& stateName) {
    auto it = states.find(stateName);
    if (it != states.end()) {
        currentState = stateName;
        animator.Play(it->second.animation.get()); // Reinicia animación al cambiar de estado
    }
}

/**
 * @brief Evalúa las condiciones de transición y actualiza la animación activa.
 */
void AnimationStateMachine::Update(float deltaTime) {
    // Verifica si hay transición activa desde el estado actual
    auto it = states.find(currentState);
    if (it != states.end()) {
        for (const auto& transition : it->second.transitions) {
            if (transition.condition && transition.condition()) {
                SetState(transition.targetState); // Transición válida → cambiar de estado
                break;
            }
        }
    }

    // Avanza la animación del estado actual
    animator.Update(deltaTime);
}

/**
 * @brief Devuelve el frame actual de la animación en curso.
 */
const SDL_Rect& AnimationStateMachine::GetCurrentFrame() const {
    return animator.GetCurrentFrameRect();
}

/**
 * @brief Devuelve el nombre del estado actual.
 */
std::string AnimationStateMachine::GetCurrentState() const {
    return currentState;
}

/**
 * @brief Devuelve una referencia a los parámetros animables.
 */
AnimationParameters& AnimationStateMachine::GetParameters() {
    return parameters;
}

/**
 * @brief Verifica si la animación actual ha terminado.
 */
bool AnimationStateMachine::IsFinished() const {
    return animator.IsFinished();
}
