#include "NavigateUpCommand.hpp"
#include "../../include/ScreenModel.hpp"

NavigateUpCommand::NavigateUpCommand(INavigationHandler &handler)
    : mHandler(handler)
{
}

void NavigateUpCommand::execute()
{
    mHandler.navigateUp();
}