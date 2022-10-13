#include "CloseCommand.hpp"

CloseCommand::CloseCommand(IOpenCloseHandler &handler)
    : ICommand()
    , mHandler(handler)
{
}

void CloseCommand::execute()
{
    mHandler.close();
}