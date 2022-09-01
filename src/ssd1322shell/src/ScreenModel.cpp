#include "../include/ScreenModel.hpp"
#include "MainScreen.hpp"
#include "MainScreenModel.hpp"
#include "MenuModel.hpp"
#include "MenuScreen.hpp"
#include <lvgl.h>

struct ScreenModelPrivate
{
    explicit ScreenModelPrivate(ScreenModel &screenModel,
                                LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                                LaptimerCore::Positioning::IPositionInformationProvider &posInfoProvider)
        : mMenuModel{screenModel}
        , mMainScreen{gpsInfoProvider}
        , mMainScreenModel{screenModel, posInfoProvider}
    {
    }

    // Screens
    MainScreen mMainScreen;
    MenuScreen mMenuScreen;

    // Screen Models
    MenuModel mMenuModel;
    MainScreenModel mMainScreenModel;
};

ScreenModel::ScreenModel(LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                         LaptimerCore::Positioning::IPositionInformationProvider &posInfoProvider)
    : mD{std::make_unique<ScreenModelPrivate>(*this, gpsInfoProvider, posInfoProvider)}
{
    // Connect to menu model view changed
    mD->mMenuModel.viewChanged.connect(&ScreenModel::activateMenuScreen, this);
}

ScreenModel::~ScreenModel() = default;

void ScreenModel::activateMainScreen()
{
    auto &mainScreenView = mD->mMainScreenModel.getActiveView();
    mD->mMainScreen.setScreenContent(&mainScreenView);
    lv_scr_load(mD->mMainScreen.getScreen());
}

void ScreenModel::activateMenuScreen()
{
    auto &menuView = mD->mMenuModel.getActiveView();
    mD->mMenuScreen.setScreenContent(&menuView);
    lv_scr_load(mD->mMenuScreen.getScreen());
}
