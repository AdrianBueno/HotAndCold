#pragma once

#include <vector>
#include <memory>
#include "../Map/IWorld.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "Commands/CommandQueue.h"


/// @brief Gestor centralizado de entidades din�micas.
/// Se encarga de actualizarlas, renderizarlas, gestionarlas y comprobar colisiones entre ellas.
/// Permite a�adir, eliminar y limpiar entidades de manera segura.
class EntityManager {
public:
    /// @brief Constructor.
    EntityManager();

    /// @brief Destructor.
    ~EntityManager();

    /// @brief A�ade una entidad al manager.
    /// @param entity Puntero �nico a la entidad a a�adir.
    void Add(std::unique_ptr<Entity> entity);

    /// @brief Actualiza todas las entidades activas.
    /// Elimina autom�ticamente entidades marcadas como inactivas.
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

    /// @brief Devuelve el n�mero de entidades activas.
    /// @return N�mero de entidades vivas.
    size_t GetEntityCount() const { return entities.size(); }

private:
    std::vector<std::unique_ptr<Entity>> entities; ///< Almac�n de entidades din�micas.
    Player* player = nullptr; // Referencia directa opcional
};
