#include "MenuScreenModel.hpp"
#include "../include/ScreenModel.hpp"

MenuScreenModel::MenuScreenModel(ScreenModel &screenModel, LaptimerCore::Session::ISessionDatabase &sessionDb)
    : NavigatableModel(mMenuEntryStack.size())
    , INavigationHandler()
    , mScreenModel(screenModel)
    , mShowMainScreenCommand(mScreenModel)
    , mNavigateUpCommand(*this)
    , mNavigateDownCommand(*this)
    , mSessionEntryModel(mSessionEntryView)
    , mWifiEntry(mWifiSettings)
    , mBluetoothEntry(mBluetoothSettings)
{
    setupSessionMenuEntry();

    // Setup Wifi Settings entry
    mWifiSettings.setCloseCommand(&mShowMainScreenCommand);
    mWifiSettings.setEntryLabel("Wi-Fi");
    mWifiSettings.setSecondaryLabel("Settings");
    mWifiSettings.setNavigateUpCommand(&mNavigateUpCommand);
    mWifiSettings.setNavigateDownCommand(&mNavigateDownCommand);

    // Setup Bluetooth Settings entry
    mBluetoothSettings.setCloseCommand(&mShowMainScreenCommand);
    mBluetoothSettings.setEntryLabel("Bluetooth");
    mBluetoothSettings.setSecondaryLabel("Settings");
    mBluetoothSettings.setNavigateUpCommand(&mNavigateUpCommand);
    mBluetoothSettings.setNavigateDownCommand(&mNavigateDownCommand);
}

View &MenuScreenModel::getActiveView() const
{
    auto index = getIndex();
    if (index > mMenuEntryStack.size())
    {
        return mMenuEntryStack[0]->getView();
    }

    return mMenuEntryStack[index]->getView();
}

void MenuScreenModel::navigateDown()
{
    decrementIndex();
    viewChanged.emit();
}

void MenuScreenModel::navigateUp()
{
    incrementIndex();
    viewChanged.emit();
}

void MenuScreenModel::onMenuEntryModelViewChanged()
{
    viewChanged.emit();
}

void MenuScreenModel::setupSessionMenuEntry()
{
    // Setup Session Settings entry
    mSessionEntryView.setCloseCommand(&mShowMainScreenCommand);
    mSessionEntryView.setEntryLabel("Session");
    mSessionEntryView.setSecondaryLabel("Settings");
    mSessionEntryView.setNavigateUpCommand(&mNavigateUpCommand);
    mSessionEntryView.setNavigateDownCommand(&mNavigateDownCommand);
    mSessionEntryModel.viewChanged.connect(&MenuScreenModel::onMenuEntryModelViewChanged, this);

    // Setup Session Sub menu entries
    mSessionOverview.setEntryLabel("Session");
    mSessionOverview.setSecondaryLabel("Overivew");
    mSessionDelete.setEntryLabel("Session");
    mSessionDelete.setSecondaryLabel("Delete");
    mSessionDeleteAll.setEntryLabel("Session");
    mSessionDeleteAll.setSecondaryLabel("Session Delete All");
    mSessionExport.setEntryLabel("Session");
    mSessionExport.setSecondaryLabel("Export");

    // Setup entry sub view
    mSessionEntryModel.addSubMenuEntry(&mSessionOverview, &mDummyListView);
    mSessionEntryModel.addSubMenuEntry(&mSessionDelete, &mDummyListView);
}
