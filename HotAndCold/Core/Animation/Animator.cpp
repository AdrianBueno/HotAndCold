#include "Animator.h"

/// @brief Comienza la reproducci�n de una nueva animaci�n.
/// Si se pasa la misma animaci�n y reset es false, no se reinicia.
/// @param animation Puntero a la animaci�n a reproducir.
/// @param reset Si es true, reinicia la animaci�n desde el principio.
void Animator::Play(Animation* animation, bool reset) {
    if (currentAnimation != animation || reset) {
        currentAnimation = animation;
        timer = 0.0f;
        currentFrame = 0;
        finished = false;
    }
}

/// @brief Avanza el estado de la animaci�n seg�n el tiempo transcurrido.
/// Calcula cu�ndo pasar al siguiente frame.
/// @param deltaTime Tiempo desde la �ltima actualizaci�n (en segundos).
void Animator::Update(float deltaTime) {
    if (!currentAnimation || finished) return;

    timer += deltaTime;
    float frameTime = currentAnimation->GetFrameTime();

    // Avanza de frame si ha pasado suficiente tiempo
    while (timer >= frameTime) {
        timer -= frameTime;
        currentFrame++;

        // Si llegamos al final de la animaci�n
        if (currentFrame >= currentAnimation->GetFrameCount()) {
            if (currentAnimation->IsLooping()) {
                currentFrame = 0;  // Repetimos desde el principio
            }
            else {
                currentFrame = currentAnimation->GetFrameCount() - 1;  // �ltimo frame
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



/// @brief Indica si la animaci�n actual ha llegado al final (si no es loop).
/// @return true si finaliz�, false si sigue activa o es loop.
bool Animator::IsFinished() const {
    return finished;
}
