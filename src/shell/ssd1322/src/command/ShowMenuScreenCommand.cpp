#include "ShowMenuScreenCommand.hpp"
#include "../../include/ScreenModel.hpp"

ShowMenuScreenCommand::ShowMenuScreenCommand(ScreenModel &screenModel)
    : mScreenModel(screenModel)
{
}

void ShowMenuScreenCommand::execute()
{
    mScreenModel.activateMenuScreen();
}