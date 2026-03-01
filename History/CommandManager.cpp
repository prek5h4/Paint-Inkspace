#include "CommandManager.h"
//#include <iostream>

void CommandManager::executeCommand(std::unique_ptr<Command> command)
{
    //std::cout << "CommandManager::executeCommand - command ptr: " << command.get() << std::endl;
    if (!command) return;
    command->execute();
    undoStack.push(std::move(command)); // After executing the command, push it onto the undo stack
    //std::cout << "Command pushed to undo stack, stack size: " << undoStack.size() << std::endl;
    // once new action happens, redo history is invalid
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void CommandManager::undo()
{
    //std::cout << "CommandManager::undo called, stack size: " << undoStack.size() << std::endl;
    if (undoStack.empty()) {
        //std::cout << "Undo stack is empty!" << std::endl;
        return;
    }
    std::unique_ptr<Command> cmd = std::move(undoStack.top());
    undoStack.pop();
    cmd->undo(); // After undoing the command, push it onto the redo stack for potential redo

    redoStack.push(std::move(cmd));
    //std::cout << "Command pushed to redo stack" << std::endl;
}

void CommandManager::redo()
{
    //std::cout << "CommandManager::redo called, stack size: " << redoStack.size() << std::endl; 
    if (redoStack.empty()) return;
    std::unique_ptr<Command> cmd = std::move(redoStack.top());
    redoStack.pop();
    cmd->execute();
    // After redoing the command, push it back onto the undo stack
    undoStack.push(std::move(cmd));
}

bool CommandManager::canUndo() const
{
    return !undoStack.empty(); //helper fns 
}

bool CommandManager::canRedo() const
{
    return !redoStack.empty(); //helper fns
}

void CommandManager::clear()
{
    while (!undoStack.empty()) {
        undoStack.pop();
    }

    while (!redoStack.empty()) {
        redoStack.pop();
    }
    //std::cout << "CommandManager::clear completed" << std::endl;
}
void CommandManager::addCommandWithoutExecute(std::unique_ptr<Command> command) {
    //std::cout << "CommandManager::addCommandWithoutExecute - command ptr: " << command.get() << std::endl;
    if (!command) return;
    // just add to undo stack and dont implement, used for move tool where shape is already moved during mouse move
    undoStack.push(std::move(command));
    //std::cout << "Command pushed to undo stack without execute, stack size: " << undoStack.size() << std::endl;

    while (!redoStack.empty()) {
        redoStack.pop();
    }
}
