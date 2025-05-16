#pragma once

#include <SDL.h>

/// @brief Clase principal del juego. Gestiona el ciclo de vida base de SDL, ventana, renderer y loop principal.
class Game {
public:
    /// @brief Constructor del juego. Inicializa punteros y estado base.
    Game();

    /// @brief Destructor del juego. Libera recursos de SDL.
    ~Game();

    /// @brief Crea una textura simple de test con color sólido.
    /// @param renderer Renderer de SDL.
    /// @param color Color a usar.
    /// @param tileSize Tamaño del tile en píxeles.
    /// @return SDL_Texture* creada.
    SDL_Texture* CreateTestTile(SDL_Renderer* renderer, SDL_Color color, int tileSize);

    /// @brief Inicializa SDL, la ventana y el renderer.
    /// @param title Título de la ventana.
    /// @param xpos Posición X de la ventana.
    /// @param ypos Posición Y de la ventana.
    /// @param width Ancho de la ventana.
    /// @param height Alto de la ventana.
    /// @param fullscreen Si es true, se crea en modo pantalla completa.
    /// @return true si la inicialización fue exitosa, false en caso de error.
    bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    /// @brief Maneja eventos SDL (solo sistema base, el InputManager manejará el detalle de input luego).
    void HandleEvents();

    /// @brief Actualiza la lógica base y delega a sistemas externos (entidades, mapa, etc.).
    void Update();

    /// @brief Renderiza toda la escena (delegará a sistemas externos en el futuro).
    void Render();

    /// @brief Limpia SDL y cierra el juego.
    void Clean();

    /// @brief Devuelve si el juego sigue activo.
    /// @return true si el juego está activo, false si debe cerrarse.
    bool Running() const;

    /// @brief Getters de acceso controlado a SDL (para sistemas externos).
    SDL_Renderer* GetRenderer() const { return renderer; }
    SDL_Window* GetWindow() const { return window; }

private:
    SDL_Window* window = nullptr;    ///< Ventana principal.
    SDL_Renderer* renderer = nullptr; ///< Renderizador principal.
    bool isRunning = false;          ///< Indica si el juego sigue activo.
};
