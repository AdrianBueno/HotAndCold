#pragma once

#include <vector>
#include <memory>
#include "../Map/IWorld.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "Commands/CommandQueue.h"


/// @brief Gestor centralizado de entidades dinámicas.
/// Se encarga de actualizarlas, renderizarlas, gestionarlas y comprobar colisiones entre ellas.
/// Permite añadir, eliminar y limpiar entidades de manera segura.
class EntityManager {
public:
    /// @brief Constructor.
    EntityManager();

    /// @brief Destructor.
    ~EntityManager();

    /// @brief Añade una entidad al manager.
    /// @param entity Puntero único a la entidad a añadir.
    void Add(std::unique_ptr<Entity> entity);

    /// @brief Actualiza todas las entidades activas.
    /// Elimina automáticamente entidades marcadas como inactivas.
    /// @param deltaTime Tiempo entre frames.
    /// @param map Referencia al TileMap.
    void Update(float deltaTime, const IWorld& world, CommandQueue& commandQueue);

    /// @brief Renderiza todas las entidades activas.
    /// @param renderer Renderer SDL.
    /// @param cameraViewport Viewport actual.
    void Render(SDL_Renderer* renderer, const SDL_Rect& cameraViewport);

    /// @brief Comprueba colisiones entre todas las entidades activas.
    /// Llama a OnCollision de ambas entidades si colisionan.
    void CheckEntityCollisions();

    /// @brief Elimina todas las entidades actuales.
    void Clear();

    /// @brief Devuelve el número de entidades activas.
    /// @return Número de entidades vivas.
    size_t GetEntityCount() const { return entities.size(); }

private:
    std::vector<std::unique_ptr<Entity>> entities; ///< Almacén de entidades dinámicas.
    Player* player = nullptr; // Referencia directa opcional
};
