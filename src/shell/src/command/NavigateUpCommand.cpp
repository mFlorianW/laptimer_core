#include "NavigateUpCommand.hpp"
#include "ScreenModel.hpp"

NavigateUpCommand::NavigateUpCommand(INavigationHandler &handler)
    : mHandler(handler)
{
}

void NavigateUpCommand::execute()
{
    mHandler.navigateUp();
}