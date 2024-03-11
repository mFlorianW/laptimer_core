#include "ShowMainScreenCommand.hpp"
#include "../../include/ScreenModel.hpp"

ShowMainScreenCommand::ShowMainScreenCommand(ScreenModel& screenModel)
    : mScreenModel(screenModel)
{
}

void ShowMainScreenCommand::execute()
{
    mScreenModel.activateMainScreen();
}