#pragma once

#include <vector>
#include <SDL.h>
#include <string>

/// @brief Representa una animación de sprites (por ejemplo caminar, saltar, etc.).
class Animation {
public:
    /// @brief Constructor.
    /// @param name Nombre identificativo de la animación.
    /// @param texture Textura que contiene los frames (sprite sheet).
    /// @param frameRects Lista de rectángulos que representan los frames en el atlas de sprites.
    /// @param frameTime Tiempo que dura cada frame (en segundos).
    /// @param loop Si es true, la animación se repite en bucle.
    Animation(const std::string& name, SDL_Texture* texture, const std::vector<SDL_Rect>& frameRects, float frameTime, bool loop);

    /// @brief Devuelve el nombre de esta animación.
    const std::string& GetName() const;

    /// @brief Devuelve todos los frames.
    const std::vector<SDL_Rect>& GetFrames() const;

    /// @brief Devuelve el rect actual de un frame dado.
    const SDL_Rect& GetFrame(size_t index) const;

    /// @brief Número total de frames.
    size_t GetFrameCount() const;

    /// @brief Duración por frame.
    float GetFrameTime() const;

    /// @brief Si la animación está en bucle.
    bool IsLooping() const;

    /// @brief Devuelve la textura usada por esta animación.
    //SDL_Texture* GetTexture() const;

private:
    std::string name;
    //SDL_Texture* texture;              ///La textura no será fija por animación.
    std::vector<SDL_Rect> frames;     ///< Lista de frames.
    float frameTime;                  ///< Duración por frame.
    bool loop;                        ///< Indica si es cíclica.
};
