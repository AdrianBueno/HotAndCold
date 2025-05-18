#pragma once

#include <SDL.h>
#include "../Managers/Commands/CommandQueue.h"

/// @brief Clase base abstracta para todas las entidades dinámicas del juego.
/// Representa elementos que tienen posición, hitbox, pueden colisionar y ser renderizadas.
class Entity {
public:
    /// @brief Constructor.
    /// @param x Posición inicial X en píxeles.
    /// @param y Posición inicial Y en píxeles.
    Entity(float x, float y);

    /// @brief Destructor virtual.
    virtual ~Entity() {}

    /// @brief Actualiza la entidad (lógica propia, animación, movimiento, colisión...).
    /// Método virtual puro que debe ser implementado por las clases derivadas.
    /// Permite a cada entidad gestionar su propia lógica teniendo acceso al mapa.
    /// @param deltaTime Tiempo entre frames (en segundos).
    /// @param map Referencia al mapa actual para permitir comprobaciones de colisión, triggers, navegación, etc.
    virtual void Update(float deltaTime, CommandQueue& queue) = 0;


    /// @brief Renderiza la entidad.
    /// Debe ser implementado por las clases derivadas.
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/cámara actual.
    virtual void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) = 0;

    

    /// @brief Comprueba colisión contra otra entidad.
    /// Las clases derivadas pueden sobreescribir este método si tienen necesidades especiales.
    /// @param other Referencia a otra entidad.
    /// @return true si colisiona, false si no.
    virtual bool CheckCollisionWithEntity(const Entity& other) const;

    /// @brief Devuelve el rectángulo del hitbox actual en el mundo (posición + hitbox).
    SDL_Rect GetHitbox() const { return hitbox; }

    /// @brief Devuelve si la entidad está activa.
    /// @return true si está activa.
    bool IsActive() const { return isActive; }

    /// @brief Marca la entidad como activa o no activa.
    /// @param active true para activar, false para desactivar.
    void SetActive(bool active) { isActive = active; }

    /// @brief Reacciona ante una colisión con otra entidad.
    /// Debe ser implementado por cada clase derivada que quiera reaccionar a colisiones.
    /// @param other Referencia a la otra entidad con la que colisiona.
    virtual void OnCollision(Entity& other) {};



    float GetX() const { return posX; }
    float GetY() const { return posY; }
    void SetX(float x) { posX = x; }
    void SetY(float y) { posY = y; }



protected:
    float posX;        ///< Posición horizontal en píxeles.
    float posY;        ///< Posición vertical en píxeles.
    SDL_Rect hitbox;   ///< Hitbox relativo a posX, posY. Definido por la entidad concreta.
    bool isActive = true; ///< Si está activa o debe ser eliminada.
    int zIndex = 0;    ///< Prioridad de render opcional (0 por defecto).
};
