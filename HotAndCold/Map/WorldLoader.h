#pragma once

#include <SDL.h>
#include "IWorld.h"

/// @brief Clase responsable de crear, cargar y configurar mundos.
/// Permite desacoplar la creación de mundos de la lógica principal del juego.
/// Puede ampliarse fácilmente para soportar cargas desde archivos, generación procedural, etc.
class WorldLoader {
public:
    /// @brief Crea un mundo de prueba con tiles básicos de colores.
    /// Este método devuelve un IWorld* que debe ser liberado por quien lo utiliza.
    /// @param renderer Renderer de SDL usado para crear las texturas de tiles.
    /// @return IWorld* ya preparado.
    static IWorld* CreateTestWorld(SDL_Renderer* renderer);
};
