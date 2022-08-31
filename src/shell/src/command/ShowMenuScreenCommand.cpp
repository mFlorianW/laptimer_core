#include "ShowMenuScreenCommand.hpp"
#include "ScreenModel.hpp"

ShowMenuScreenCommand::ShowMenuScreenCommand(ScreenModel &screenModel)
    : mScreenModel(screenModel)
{
}

void ShowMenuScreenCommand::execute()
{
    mScreenModel.activateMenuScreen();
}