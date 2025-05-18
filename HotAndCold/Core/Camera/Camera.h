#pragma once

#include <SDL.h>
#include "../../Entities/Entity.h"

/// @brief Sistema de c�mara independiente y avanzada para juegos 2D.
/// Soporta seguimiento con zona muerta, l�mites, interpolaci�n suave, zoom b�sico y scripting (modos de c�mara).
class Camera {
public:
    /// @brief Modos de comportamiento de la c�mara.
    enum CameraMode {
        FOLLOW, ///< Sigue a la entidad objetivo.
        FIXED   ///< Permanece en una posici�n fija.
    };

    /// @brief Constructor.
    /// @param screenWidth Ancho de la ventana.
    /// @param screenHeight Alto de la ventana.
    Camera(int screenWidth, int screenHeight);

    /// @brief Define la entidad objetivo que la c�mara seguir�.
    /// @param target Entidad a seguir.
    void SetTarget(Entity* target);

    /// @brief Actualiza la c�mara aplicando zona muerta, interpolaci�n y l�mites.
	/// @param window Ventana SDL para obtener el tama�o.
    /// Debe llamarse una vez por frame.
    void Update(SDL_Window* window);

    /// @brief Devuelve el viewport actual (SDL_Rect).
    SDL_Rect GetViewport() const { return viewport; }

    /// @brief Configura el tama�o de la zona muerta (dead zone) centrada en la pantalla.
    /// @param width Ancho de la zona muerta.
    /// @param height Alto de la zona muerta.
    void SetDeadZoneSize(int width, int height);

    /// @brief Define los l�mites del mundo/mapa para evitar mostrar fuera del �rea v�lida.
    /// @param worldBounds Rect�ngulo que delimita el mapa.
    void SetLimits(const SDL_Rect& worldBounds);

    /// @brief Configura el modo de c�mara (FOLLOW, FIXED).
    /// @param mode Modo deseado.
    void SetMode(CameraMode mode);

    /// @brief Define la posici�n fija de la c�mara (cuando est� en modo FIXED).
    /// @param x Posici�n X.
    /// @param y Posici�n Y.
    void SetFixedPosition(int x, int y);

    /// @brief Ajusta el factor de zoom.
    /// @param zoomFactor Zoom deseado (1.0 = normal, >1 = acercar, <1 = alejar).
    void SetZoom(float zoomFactor);

    /// @brief Devuelve el factor de zoom actual.
    float GetZoom() const { return zoom; }

	/// @brief Actualizar el viewport de la c�mara seg�n la ventana SDL.
    void UpdateViewportFromWindow(SDL_Window* window);

    /// @brief Recalcula el tama�o de la zona muerta seg�n el porcentaje del viewport actual.
    /// @param percentage Porcentaje (ej: 0.15f para 15%).
    void RecalculateDeadZone(float percentage);


private:
    SDL_Rect viewport;      ///< Viewport actual de la c�mara.
    SDL_Rect deadZone;      ///< Zona muerta centrada en pantalla.
    SDL_Rect limits;        ///< L�mites del mundo/mapa.
    Entity* target = nullptr; ///< Entidad objetivo a seguir.
    CameraMode mode = FOLLOW; ///< Modo actual de la c�mara.
    SDL_Point fixedPosition = { 0, 0 }; ///< Posici�n fija cuando est� en modo FIXED.
    float zoom = 1.0f;        ///< Factor de zoom actual.

    /// @brief Interpolaci�n suave entre valores (lerp cl�sico).
    float Lerp(float a, float b, float t) const;
};
