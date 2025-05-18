#pragma once

#include <string>
#include <unordered_map>

/**
 * @brief Tipos de parámetros que puede usar la máquina de estados de animación.
 */
enum class AnimationParameterType {
    Bool,
    Float,
    Trigger
};

/**
 * @brief Representa un parámetro individual que puede influir en las transiciones de animación.
 */
struct AnimationParameter {
    AnimationParameterType type;

    // Valores posibles
    bool boolValue;
    float floatValue;
    bool triggerConsumed; ///< Solo para triggers, se consume tras activarse

    AnimationParameter() : type(AnimationParameterType::Bool), boolValue(false), floatValue(0.0f), triggerConsumed(false) {}

    explicit AnimationParameter(bool b)
        : type(AnimationParameterType::Bool), boolValue(b), floatValue(0.0f), triggerConsumed(false) {
    }

    explicit AnimationParameter(float f)
        : type(AnimationParameterType::Float), boolValue(false), floatValue(f), triggerConsumed(false) {
    }

    static AnimationParameter Trigger() {
        AnimationParameter p;
        p.type = AnimationParameterType::Trigger;
        p.boolValue = true;
        p.triggerConsumed = false;
        return p;
    }
};

/**
 * @brief Contenedor de todos los parámetros de animación que se usan en condiciones de transición.
 */
class AnimationParameters {
public:
    /**
     * @brief Establece un parámetro booleano.
     */
    void SetBool(const std::string& name, bool value);

    /**
     * @brief Establece un parámetro numérico (float).
     */
    void SetFloat(const std::string& name, float value);

    /**
     * @brief Dispara un parámetro tipo trigger.
     */
    void SetTrigger(const std::string& name);

    /**
     * @brief Lee un valor booleano. Retorna false si no existe o no es bool.
     */
    bool GetBool(const std::string& name) const;

    /**
     * @brief Lee un valor float. Retorna 0.0f si no existe o no es float.
     */
    float GetFloat(const std::string& name) const;

    /**
     * @brief Consume un trigger. Devuelve true solo la primera vez que se llama después de SetTrigger.
     */
    bool ConsumeTrigger(const std::string& name);

private:
    std::unordered_map<std::string, AnimationParameter> parameters;
};
