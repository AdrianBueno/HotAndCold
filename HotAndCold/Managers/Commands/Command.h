// Command.h
#pragma once

class EntityManager;

/// @brief Comando abstracto base. Todos los comandos heredan de este.
class Command {
public:
    virtual ~Command() {}
    virtual void Execute(EntityManager& entityManager) = 0;
};
