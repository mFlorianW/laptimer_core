#include "NavigateDownCommand.hpp"
#include "ScreenModel.hpp"

NavigateDownCommand::NavigateDownCommand(INavigationHandler &handler)
    : mHandler(handler)
{
}

void NavigateDownCommand::execute()
{
    mHandler.navigateDown();
}