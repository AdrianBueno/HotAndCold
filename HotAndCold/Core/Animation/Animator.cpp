#include "Animator.h"

/// @brief Comienza la reproducción de una nueva animación.
/// Si se pasa la misma animación y reset es false, no se reinicia.
/// @param animation Puntero a la animación a reproducir.
/// @param reset Si es true, reinicia la animación desde el principio.
void Animator::Play(Animation* animation, bool reset) {
    if (currentAnimation != animation || reset) {
        currentAnimation = animation;
        timer = 0.0f;
        currentFrame = 0;
        finished = false;
    }
}

/// @brief Avanza el estado de la animación según el tiempo transcurrido.
/// Calcula cuándo pasar al siguiente frame.
/// @param deltaTime Tiempo desde la última actualización (en segundos).
void Animator::Update(float deltaTime) {
    if (!currentAnimation || finished) return;

    timer += deltaTime;
    float frameTime = currentAnimation->GetFrameTime();

    // Avanza de frame si ha pasado suficiente tiempo
    while (timer >= frameTime) {
        timer -= frameTime;
        currentFrame++;

        // Si llegamos al final de la animación
        if (currentFrame >= currentAnimation->GetFrameCount()) {
            if (currentAnimation->IsLooping()) {
                currentFrame = 0;  // Repetimos desde el principio
            }
            else {
                currentFrame = currentAnimation->GetFrameCount() - 1;  // Último frame
                finished = true;
                break;
            }
        }
    }
}

/// @brief Devuelve el rect actual (frame) que se debe renderizar.
/// @return SDL_Rect del frame actual.
SDL_Rect Animator::GetCurrentFrameRect() const {
    if (!currentAnimation) {
        static SDL_Rect empty = { 0, 0, 0, 0 };
        return empty;
    }
    return currentAnimation->GetFrame(currentFrame);
}



/// @brief Indica si la animación actual ha llegado al final (si no es loop).
/// @return true si finalizó, false si sigue activa o es loop.
bool Animator::IsFinished() const {
    return finished;
}
