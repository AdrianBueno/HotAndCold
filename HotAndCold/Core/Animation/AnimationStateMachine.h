#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "Animation.h"
#include "Animator.h"
#include "AnimationParameters.h"
#include "AnimationStateNode.h"

/**
 * @brief Máquina de estados de animación flexible con soporte para condiciones dinámicas.
 *
 * Reemplaza al diseño anterior basado en enums, permitiendo transiciones entre estados
 * basadas en valores de parámetros (bool, float, trigger).
 */
class AnimationStateMachine {
public:
    /**
     * @brief Añade un nuevo estado con una animación asociada.
     * @param stateName Nombre identificador del estado.
     * @param animation Animación asociada.
     */
    void AddState(const std::string& stateName, const std::shared_ptr<Animation> animation);

    /**
     * @brief Añade una transición condicional entre dos estados.
     * @param from Estado de origen.
     * @param to Estado de destino.
     * @param condition Función que retorna true si debe hacerse la transición.
     */
    void AddTransition(const std::string& from, const std::string& to, std::function<bool()> condition);

    /**
     * @brief Cambia manualmente el estado actual, reiniciando la animación.
     * @param stateName Nombre del nuevo estado.
     */
    void SetState(const std::string& stateName);

    /**
     * @brief Actualiza la animación activa y evalúa transiciones.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     */
    void Update(float deltaTime);

    /**
     * @brief Obtiene el frame actual de la animación activa.
     * @return Frame actual como SDL_Rect.
     */
    const SDL_Rect& GetCurrentFrame() const;

    /**
     * @brief Retorna el nombre del estado actual.
     */
    std::string GetCurrentState() const;

    /**
     * @brief Acceso a los parámetros animables del sistema.
     * @return Referencia a los parámetros.
     */
    AnimationParameters& GetParameters();

    /**
     * @brief Indica si la animación actual ha terminado.
     * @return true si terminó, false si sigue activa.
     */
    bool IsFinished() const;

private:
    std::unordered_map<std::string, AnimationStateNode> states; ///< Estados disponibles
    std::string currentState; ///< Estado activo
    Animator animator; ///< Controlador de reproducción
    AnimationParameters parameters; ///< Parámetros animables
};
