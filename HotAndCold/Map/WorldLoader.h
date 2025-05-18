#pragma once

#include <SDL.h>
#include "IWorld.h"

/// @brief Clase responsable de crear, cargar y configurar mundos.
/// Permite desacoplar la creaci�n de mundos de la l�gica principal del juego.
/// Puede ampliarse f�cilmente para soportar cargas desde archivos, generaci�n procedural, etc.
class WorldLoader {
public:
    /// @brief Crea un mundo de prueba con tiles b�sicos de colores.
    /// Este m�todo devuelve un IWorld* que debe ser liberado por quien lo utiliza.
    /// @param renderer Renderer de SDL usado para crear las texturas de tiles.
    /// @return IWorld* ya preparado.
    static IWorld* CreateTestWorld(SDL_Renderer* renderer);
};
