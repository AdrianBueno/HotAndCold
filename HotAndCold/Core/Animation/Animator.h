#pragma once

#include "Animation.h"

/// @brief Controla la reproducción de una animación (frame actual, tiempo, etc.).
class Animator {
public:
    /// @brief Inicia la reproducción de una animación.
    /// @param animation Puntero a la animación a reproducir.
    /// @param reset Si es true, reinicia la animación desde el primer frame.
    void Play(Animation* animation, bool reset = false);

    /// @brief Actualiza el estado de la animación en función del tiempo transcurrido.
    /// @param deltaTime Tiempo transcurrido desde la última actualización (en segundos).
    void Update(float deltaTime);

    /// @brief Obtiene el rectángulo del frame actual.
    /// @return SDL_Rect correspondiente al frame actual.
    SDL_Rect GetCurrentFrameRect() const;

    /// @brief Obtiene la textura asociada a la animación actual.
    /// @return Puntero a SDL_Texture de la animación actual.
    //SDL_Texture* GetCurrentTexture() const;

    /// @brief Verifica si la animación actual ha finalizado.
    /// @return true si la animación ha terminado; false en caso contrario.
    bool IsFinished() const;

private:
    Animation* currentAnimation = nullptr;
    float timer = 0.0f;
    size_t currentFrame = 0;
    bool finished = false;
};
