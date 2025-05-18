// CommandQueue.h
#pragma once

#include <queue>
#include <memory> // Necesario para std::unique_ptr
#include "Command.h"

/// @brief Cola FIFO de comandos.
class CommandQueue {
public:
    void Enqueue(std::unique_ptr<Command> command) {
        commands.push(std::move(command));
    }

    void Process(class EntityManager& entityManager) {
        while (!commands.empty()) {
            commands.front()->Execute(entityManager);
            commands.pop();
        }
    }

private:
    std::queue<std::unique_ptr<Command>> commands;
};
