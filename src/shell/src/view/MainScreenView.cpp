#include "MainScreenView.hpp"
#include <cstdio>

bool MainScreenView::handleEnter()
{
    if (mNavigateMenuCommand == nullptr)
    {
        return false;
    }

    mNavigateMenuCommand->execute();
    return true;
}

void MainScreenView::setShowMenuScreenCommand(ICommand *command)
{
    mNavigateMenuCommand = command;
}