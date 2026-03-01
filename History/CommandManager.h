#pragma once
#include <stack>
#include <memory>
#include "../Commands/Command.h"


class CommandManager {
public:
    void executeCommand(std::unique_ptr<Command> command);
    void addCommandWithoutExecute(std::unique_ptr<Command> command);
    void undo();
    void redo();

    bool canUndo() const;
    bool canRedo() const;

    void clear();

private:
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;
};