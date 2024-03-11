#include "MainScreenView.hpp"
#include <cstdio>

void MainScreenView::handleEnter()
{
    if (mNavigateMenuCommand == nullptr) {
        return;
    }

    mNavigateMenuCommand->execute();
}

void MainScreenView::setShowMenuScreenCommand(ICommand* command)
{
    mNavigateMenuCommand = command;
}
