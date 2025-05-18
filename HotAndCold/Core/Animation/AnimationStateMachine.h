#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "Animation.h"
#include "Animator.h"
#include "AnimationParameters.h"
#include "AnimationStateNode.h"

/**
 * @brief M�quina de estados de animaci�n flexible con soporte para condiciones din�micas.
 *
 * Reemplaza al dise�o anterior basado en enums, permitiendo transiciones entre estados
 * basadas en valores de par�metros (bool, float, trigger).
 */
class AnimationStateMachine {
public:
    /**
     * @brief A�ade un nuevo estado con una animaci�n asociada.
     * @param stateName Nombre identificador del estado.
     * @param animation Animaci�n asociada.
     */
    void AddState(const std::string& stateName, const std::shared_ptr<Animation> animation);

    /**
     * @brief A�ade una transici�n condicional entre dos estados.
     * @param from Estado de origen.
     * @param to Estado de destino.
     * @param condition Funci�n que retorna true si debe hacerse la transici�n.
     */
    void AddTransition(const std::string& from, const std::string& to, std::function<bool()> condition);

    /**
     * @brief Cambia manualmente el estado actual, reiniciando la animaci�n.
     * @param stateName Nombre del nuevo estado.
     */
    void SetState(const std::string& stateName);

    /**
     * @brief Actualiza la animaci�n activa y eval�a transiciones.
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
     */
    void Update(float deltaTime);

    /**
     * @brief Obtiene el frame actual de la animaci�n activa.
     * @return Frame actual como SDL_Rect.
     */
    const SDL_Rect& GetCurrentFrame() const;

    /**
     * @brief Retorna el nombre del estado actual.
     */
    std::string GetCurrentState() const;

    /**
     * @brief Acceso a los par�metros animables del sistema.
     * @return Referencia a los par�metros.
     */
    AnimationParameters& GetParameters();

    /**
     * @brief Indica si la animaci�n actual ha terminado.
     * @return true si termin�, false si sigue activa.
     */
    bool IsFinished() const;

private:
    std::unordered_map<std::string, AnimationStateNode> states; ///< Estados disponibles
    std::string currentState; ///< Estado activo
    Animator animator; ///< Controlador de reproducci�n
    AnimationParameters parameters; ///< Par�metros animables
};
