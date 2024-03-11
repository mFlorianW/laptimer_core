#include "MenuScreenModel.hpp"
#include "../include/ScreenModel.hpp"

MenuScreenModel::MenuScreenModel(ScreenModel& screenModel, LaptimerCore::Storage::ISessionDatabase& sessionDb)
    : mScreenModel(screenModel)
    , mSessionViewModelEntry{sessionDb}
    , mSessionView{mSessionViewModelEntry}
{
    setupBluetoothMenu();
    setupSessionMenu();

    setupRootMenu();
}

View& MenuScreenModel::getActiveView() const
{
    return *mRootMenu.getMenuEntryView();
}

void MenuScreenModel::setupBluetoothMenu()
{
    mRootBluetoohMenuView.setEntryLabel("WLAN");
    mRootBluetoohMenuView.setSecondaryLabel("Settings");
    mRootBluetoohMenuEntry.setMenuEntryView(&mRootBluetoohMenuView);
}

void MenuScreenModel::setupSessionMenu()
{
    mSessionViewModelEntry.setMenuEntryView(&mSessionView);

    mSessionOverviewView.setEntryLabel("Session");
    mSessionOverviewView.setSecondaryLabel("Overview");
    mSessionOverviewEntry.setMenuEntryView(&mSessionOverviewView);
    mSessionOverviewEntry.addMenuEntry(&mSessionViewModelEntry);

    mSessionDeleteAllView.setEntryLabel("Session");
    mSessionDeleteAllView.setSecondaryLabel("Delete All");
    mSessionDeleteAllEntry.setMenuEntryView(&mSessionDeleteAllView);

    mSessionDetailMenu.addMenuEntry(&mSessionOverviewEntry);
    mSessionDetailMenu.addMenuEntry(&mSessionDeleteAllEntry);

    mRootSessionMenuView.setEntryLabel("Session");
    mRootSessionMenuView.setSecondaryLabel("Settings");
    mRootSessionMenuEntry.setMenuEntryView(&mRootSessionMenuView);

    mRootSessionMenuEntry.addMenuEntry(&mSessionDetailMenu);
}

void MenuScreenModel::setupRootMenu()
{
    mRootMenu.addMenuEntry(&mRootSessionMenuEntry);
    mRootMenu.addMenuEntry(&mRootBluetoohMenuEntry);

    mRootMenu.viewChanged.connect(&MenuScreenModel::handleMenuViewChanged, this);
    mRootMenu.closeEntry.connect(&MenuScreenModel::handleCloseEntry, this);
}

void MenuScreenModel::handleMenuViewChanged()
{
    viewChanged.emit();
}

void MenuScreenModel::handleCloseEntry()
{
    closeMenu.emit();
}
