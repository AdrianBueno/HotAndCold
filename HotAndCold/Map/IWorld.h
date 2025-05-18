#pragma once

#include <SDL.h>

/// @brief Interfaz abstracta que representa el mundo (tilemap, colisiones, triggers...).
/// Permite a las entidades consultar el entorno sin depender de clases concretas.
class IWorld {
public:
    virtual ~IWorld() = default;

    /// @brief Comprueba si una celda en el mapa es s�lida.
    /// @param x Celda en X.
    /// @param y Celda en Y.
    /// @return true si es s�lida.
    virtual bool IsSolidAt(int x, int y) const = 0;

    /// @brief Devuelve el tama�o de cada tile en p�xeles.
    virtual int GetTileSize() const = 0;

    /// @brief Devuelve el ancho total del mundo en tiles.
    virtual int GetWidth() const = 0;

    /// @brief Devuelve el alto total del mundo en tiles.
    virtual int GetHeight() const = 0;
};
