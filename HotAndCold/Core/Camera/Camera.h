#pragma once

#include <SDL.h>
#include "../../Entities/Entity.h"

/// @brief Sistema de cámara independiente y avanzada para juegos 2D.
/// Soporta seguimiento con zona muerta, límites, interpolación suave, zoom básico y scripting (modos de cámara).
class Camera {
public:
    /// @brief Modos de comportamiento de la cámara.
    enum CameraMode {
        FOLLOW, ///< Sigue a la entidad objetivo.
        FIXED   ///< Permanece en una posición fija.
    };

    /// @brief Constructor.
    /// @param screenWidth Ancho de la ventana.
    /// @param screenHeight Alto de la ventana.
    Camera(int screenWidth, int screenHeight);

    /// @brief Define la entidad objetivo que la cámara seguirá.
    /// @param target Entidad a seguir.
    void SetTarget(Entity* target);

    /// @brief Actualiza la cámara aplicando zona muerta, interpolación y límites.
	/// @param window Ventana SDL para obtener el tamaño.
    /// Debe llamarse una vez por frame.
    void Update(SDL_Window* window);

    /// @brief Devuelve el viewport actual (SDL_Rect).
    SDL_Rect GetViewport() const { return viewport; }

    /// @brief Configura el tamaño de la zona muerta (dead zone) centrada en la pantalla.
    /// @param width Ancho de la zona muerta.
    /// @param height Alto de la zona muerta.
    void SetDeadZoneSize(int width, int height);

    /// @brief Define los límites del mundo/mapa para evitar mostrar fuera del área válida.
    /// @param worldBounds Rectángulo que delimita el mapa.
    void SetLimits(const SDL_Rect& worldBounds);

    /// @brief Configura el modo de cámara (FOLLOW, FIXED).
    /// @param mode Modo deseado.
    void SetMode(CameraMode mode);

    /// @brief Define la posición fija de la cámara (cuando está en modo FIXED).
    /// @param x Posición X.
    /// @param y Posición Y.
    void SetFixedPosition(int x, int y);

    /// @brief Ajusta el factor de zoom.
    /// @param zoomFactor Zoom deseado (1.0 = normal, >1 = acercar, <1 = alejar).
    void SetZoom(float zoomFactor);

    /// @brief Devuelve el factor de zoom actual.
    float GetZoom() const { return zoom; }

	/// @brief Actualizar el viewport de la cámara según la ventana SDL.
    void UpdateViewportFromWindow(SDL_Window* window);

    /// @brief Recalcula el tamaño de la zona muerta según el porcentaje del viewport actual.
    /// @param percentage Porcentaje (ej: 0.15f para 15%).
    void RecalculateDeadZone(float percentage);


private:
    SDL_Rect viewport;      ///< Viewport actual de la cámara.
    SDL_Rect deadZone;      ///< Zona muerta centrada en pantalla.
    SDL_Rect limits;        ///< Límites del mundo/mapa.
    Entity* target = nullptr; ///< Entidad objetivo a seguir.
    CameraMode mode = FOLLOW; ///< Modo actual de la cámara.
    SDL_Point fixedPosition = { 0, 0 }; ///< Posición fija cuando está en modo FIXED.
    float zoom = 1.0f;        ///< Factor de zoom actual.

    /// @brief Interpolación suave entre valores (lerp clásico).
    float Lerp(float a, float b, float t) const;
};
