#pragma once

#include <SDL.h>
#include "../Managers/Commands/CommandQueue.h"

/// @brief Clase base abstracta para todas las entidades din�micas del juego.
/// Representa elementos que tienen posici�n, hitbox, pueden colisionar y ser renderizadas.
class Entity {
public:
    /// @brief Constructor.
    /// @param x Posici�n inicial X en p�xeles.
    /// @param y Posici�n inicial Y en p�xeles.
    Entity(float x, float y);

    /// @brief Destructor virtual.
    virtual ~Entity() {}

    /// @brief Actualiza la entidad (l�gica propia, animaci�n, movimiento, colisi�n...).
    /// M�todo virtual puro que debe ser implementado por las clases derivadas.
    /// Permite a cada entidad gestionar su propia l�gica teniendo acceso al mapa.
    /// @param deltaTime Tiempo entre frames (en segundos).
    /// @param map Referencia al mapa actual para permitir comprobaciones de colisi�n, triggers, navegaci�n, etc.
    virtual void Update(float deltaTime, CommandQueue& queue) = 0;


    /// @brief Renderiza la entidad.
    /// Debe ser implementado por las clases derivadas.
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport/c�mara actual.
    virtual void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport) = 0;

    

    /// @brief Comprueba colisi�n contra otra entidad.
    /// Las clases derivadas pueden sobreescribir este m�todo si tienen necesidades especiales.
    /// @param other Referencia a otra entidad.
    /// @return true si colisiona, false si no.
    virtual bool CheckCollisionWithEntity(const Entity& other) const;

    /// @brief Devuelve el rect�ngulo del hitbox actual en el mundo (posici�n + hitbox).
    SDL_Rect GetHitbox() const { return hitbox; }

    /// @brief Devuelve si la entidad est� activa.
    /// @return true si est� activa.
    bool IsActive() const { return isActive; }

    /// @brief Marca la entidad como activa o no activa.
    /// @param active true para activar, false para desactivar.
    void SetActive(bool active) { isActive = active; }

    /// @brief Reacciona ante una colisi�n con otra entidad.
    /// Debe ser implementado por cada clase derivada que quiera reaccionar a colisiones.
    /// @param other Referencia a la otra entidad con la que colisiona.
    virtual void OnCollision(Entity& other) {};



    float GetX() const { return posX; }
    float GetY() const { return posY; }
    void SetX(float x) { posX = x; }
    void SetY(float y) { posY = y; }



protected:
    float posX;        ///< Posici�n horizontal en p�xeles.
    float posY;        ///< Posici�n vertical en p�xeles.
    SDL_Rect hitbox;   ///< Hitbox relativo a posX, posY. Definido por la entidad concreta.
    bool isActive = true; ///< Si est� activa o debe ser eliminada.
    int zIndex = 0;    ///< Prioridad de render opcional (0 por defecto).
};
