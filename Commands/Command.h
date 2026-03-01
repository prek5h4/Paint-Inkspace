#pragma once
#include <memory>

class Command {
public:
    virtual ~Command() = default;
    // Apply the action (redo)
    virtual void execute() = 0;
    virtual void undo() = 0;

};
