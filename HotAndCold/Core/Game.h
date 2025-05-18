#pragma once

#include <SDL.h>

/// @brief Clase principal del juego.
/// Gestiona el ciclo de vida completo: inicialización, eventos, actualización, render y limpieza.
/// Coordina SDL2, ventana, renderer, sistemas externos (EntityManager, Camera, InputManager...).
class Game {
public:
    /// @brief Constructor del juego. Inicializa punteros y estado base.
    Game();

    /// @brief Destructor del juego. Libera todos los recursos y cierra SDL.
    ~Game();

    /// @brief Crea una textura simple de color sólido (para tests o debug).
    /// @param renderer Renderer de SDL.
    /// @param color Color del tile.
    /// @param tileSize Tamaño del tile en píxeles.
    /// @return Puntero a la textura creada.
    SDL_Texture* CreateTestTile(SDL_Renderer* renderer, SDL_Color color, int tileSize);

    /// @brief Inicializa SDL2, crea ventana, renderer y configura el juego.
    /// @param title Título de la ventana.
    /// @param xpos Posición X inicial de la ventana.
    /// @param ypos Posición Y inicial de la ventana.
    /// @param width Ancho de la ventana en píxeles.
    /// @param height Alto de la ventana en píxeles.
    /// @param fullscreen Si es true, arranca en pantalla completa.
    /// @return true si todo fue correcto, false si hubo errores.
    bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    /// @brief Maneja eventos SDL de entrada (ventana, teclado, ratón...).
    /// InputManager procesará el detalle, aquí solo se recolectan eventos.
    void HandleEvents();

    /// @brief Actualiza la lógica del juego completa.
    /// Procesa input, entidades, colisiones, cámara, etc.
    void Update();

    /// @brief Renderiza la escena completa.
    /// Incluye mapa, entidades y elementos de debug.
    void Render();

    /// @brief Limpia y libera todos los recursos del juego.
    void Clean();

    /// @brief Devuelve si el juego sigue ejecutándose.
    /// @return true si está activo, false si debe cerrarse.
    bool Running() const;

    /// @brief Getter seguro del renderer SDL2.
    /// @return SDL_Renderer* actual.
    SDL_Renderer* GetRenderer() const { return renderer; }

    /// @brief Getter seguro de la ventana SDL2.
    /// @return SDL_Window* actual.
    SDL_Window* GetWindow() const { return window; }

private:
    SDL_Window* window = nullptr;      ///< Ventana principal SDL.
    SDL_Renderer* renderer = nullptr;  ///< Renderizador principal SDL.
    bool isRunning = false;            ///< Estado de ejecución del juego.
};
