#include "AnimationParameters.h"

/**
 * @brief Establece un parámetro booleano, creándolo si no existe.
 */
void AnimationParameters::SetBool(const std::string& name, bool value) {
    parameters[name] = AnimationParameter(value);
}

/**
 * @brief Establece un parámetro flotante, creándolo si no existe.
 */
void AnimationParameters::SetFloat(const std::string& name, float value) {
    parameters[name] = AnimationParameter(value);
}

/**
 * @brief Dispara un parámetro trigger. Si ya existía, lo reactiva.
 */
void AnimationParameters::SetTrigger(const std::string& name) {
    parameters[name] = AnimationParameter::Trigger();
}

/**
 * @brief Devuelve el valor booleano del parámetro, o false si no existe o no es del tipo adecuado.
 */
bool AnimationParameters::GetBool(const std::string& name) const {
    auto it = parameters.find(name);
    if (it != parameters.end() && it->second.type == AnimationParameterType::Bool) {
        return it->second.boolValue;
    }
    return false;
}

/**
 * @brief Devuelve el valor flotante del parámetro, o 0.0f si no existe o no es del tipo adecuado.
 */
float AnimationParameters::GetFloat(const std::string& name) const {
    auto it = parameters.find(name);
    if (it != parameters.end() && it->second.type == AnimationParameterType::Float) {
        return it->second.floatValue;
    }
    return 0.0f;
}

/**
 * @brief Consume un trigger. Retorna true solo una vez después de ser disparado.
 */
bool AnimationParameters::ConsumeTrigger(const std::string& name) {
    auto it = parameters.find(name);
    if (it != parameters.end() && it->second.type == AnimationParameterType::Trigger) {
        if (!it->second.triggerConsumed) {
            it->second.triggerConsumed = true;
            return true;
        }
    }
    return false;
}
