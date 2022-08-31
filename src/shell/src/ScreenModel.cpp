#include "ScreenModel.hpp"
#include <lvgl.h>

ScreenModel::ScreenModel(LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                         LaptimerCore::Positioning::IPositionInformationProvider &posInfoProvider)
    : mMenuModel{*this}
    , mMainScreen{gpsInfoProvider}
    , mMainScreenModel{*this, posInfoProvider}
{
    // Connect to menu model view changed
    mMenuModel.viewChanged.connect(&ScreenModel::activateMenuScreen, this);
}

void ScreenModel::activateMainScreen()
{
    auto &mainScreenView = mMainScreenModel.getActiveView();
    mMainScreen.setScreenContent(&mainScreenView);
    lv_scr_load(mMainScreen.getScreen());
}

void ScreenModel::activateMenuScreen()
{
    auto &menuView = mMenuModel.getActiveView();
    mMenuScreen.setScreenContent(&menuView);
    lv_scr_load(mMenuScreen.getScreen());
}
