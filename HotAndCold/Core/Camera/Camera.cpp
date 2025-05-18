#include "Camera.h"
#include <algorithm>

/// @brief Helper interno para clamp manual (compatibilidad con C++11, C++14).
template <typename T>
T Clamp(T value, T min, T max) {
    return (value < min) ? min : (value > max) ? max : value;
}

Camera::Camera(int screenWidth, int screenHeight) {
    viewport = { 0, 0, screenWidth, screenHeight };
    SetDeadZoneSize(screenWidth / 4, screenHeight / 4); // Dead zone por defecto (25% del tamaño pantalla)
    limits = { 0, 0, 10000, 10000 }; // Límites grandes por defecto
}

void Camera::SetTarget(Entity* target) {
    this->target = target;
}

void Camera::SetDeadZoneSize(int width, int height) {
    deadZone.w = width;
    deadZone.h = height;
}

void Camera::RecalculateDeadZone(float percentage) {
    deadZone.w = static_cast<int>(viewport.w * percentage);
    deadZone.h = static_cast<int>(viewport.h * percentage);
}


void Camera::SetLimits(const SDL_Rect& worldBounds) {
    limits = worldBounds;
}

void Camera::SetMode(CameraMode mode) {
    this->mode = mode;
}

void Camera::SetFixedPosition(int x, int y) {
    fixedPosition = { x, y };
}

void Camera::SetZoom(float zoomFactor) {
    zoom = std::max(0.1f, zoomFactor);
}

float Camera::Lerp(float a, float b, float t) const {
    return a + (b - a) * t;
}

void Camera::Update(SDL_Window* window) {
    this->UpdateViewportFromWindow(window);
    this->RecalculateDeadZone(0.15f); // Ahora sí, correctamente
    if (mode == FOLLOW && target) {
        // Centrar la dead zone en el viewport actual
        deadZone.x = viewport.x + (viewport.w - deadZone.w) / 2;
        deadZone.y = viewport.y + (viewport.h - deadZone.h) / 2;

        SDL_Point targetPos = { static_cast<int>(target->GetX()), static_cast<int>(target->GetY()) };

        // Comprobar si el target ha salido por izquierda o derecha
        if (targetPos.x < deadZone.x)
            viewport.x -= (deadZone.x - targetPos.x);
        else if (targetPos.x > deadZone.x + deadZone.w)
            viewport.x += (targetPos.x - (deadZone.x + deadZone.w));

        // Comprobar si el target ha salido por arriba o abajo
        if (targetPos.y < deadZone.y)
            viewport.y -= (deadZone.y - targetPos.y);
        else if (targetPos.y > deadZone.y + deadZone.h)
            viewport.y += (targetPos.y - (deadZone.y + deadZone.h));
    }
    else if (mode == FIXED) {
        viewport.x = fixedPosition.x - (viewport.w / 2);
        viewport.y = fixedPosition.y - (viewport.h / 2);
    }

    // Aplicar límites finales
    viewport.x = Clamp(viewport.x, limits.x, limits.x + limits.w - viewport.w);
    viewport.y = Clamp(viewport.y, limits.y, limits.y + limits.h - viewport.h);
}




void Camera::UpdateViewportFromWindow(SDL_Window* window) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    viewport.w = width;
    viewport.h = height;
}
