#pragma once

#include "Animation.h"

/// @brief Controla la reproducci�n de una animaci�n (frame actual, tiempo, etc.).
class Animator {
public:
    /// @brief Inicia la reproducci�n de una animaci�n.
    /// @param animation Puntero a la animaci�n a reproducir.
    /// @param reset Si es true, reinicia la animaci�n desde el primer frame.
    void Play(Animation* animation, bool reset = false);

    /// @brief Actualiza el estado de la animaci�n en funci�n del tiempo transcurrido.
    /// @param deltaTime Tiempo transcurrido desde la �ltima actualizaci�n (en segundos).
    void Update(float deltaTime);

    /// @brief Obtiene el rect�ngulo del frame actual.
    /// @return SDL_Rect correspondiente al frame actual.
    SDL_Rect GetCurrentFrameRect() const;

    /// @brief Obtiene la textura asociada a la animaci�n actual.
    /// @return Puntero a SDL_Texture de la animaci�n actual.
    //SDL_Texture* GetCurrentTexture() const;

    /// @brief Verifica si la animaci�n actual ha finalizado.
    /// @return true si la animaci�n ha terminado; false en caso contrario.
    bool IsFinished() const;

private:
    Animation* currentAnimation = nullptr;
    float timer = 0.0f;
    size_t currentFrame = 0;
    bool finished = false;
};
