#include "OpenCommand.hpp"

OpenCommand::OpenCommand(IOpenCloseHandler& handler)
    : ICommand()
    , mHandler(handler)
{
}

void OpenCommand::execute()
{
    mHandler.open();
}