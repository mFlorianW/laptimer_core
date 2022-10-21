#include "../include/ScreenModel.hpp"
#include "MainScreen.hpp"
#include "MainScreenModel.hpp"
#include "MenuScreenModel.hpp"
#include "MenuScreen.hpp"
#include <lvgl.h>

struct ScreenModelPrivate
{
    explicit ScreenModelPrivate(ScreenModel &screenModel,
                                LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                                LaptimerCore::Positioning::IPositionDateTimeProvider &posDateTimeProvider,
                                LaptimerCore::Session::ISessionDatabase &sessionDatabase)
        : mMainScreen{gpsInfoProvider}
        , mMenuModel{screenModel, sessionDatabase}
        , mMainScreenModel{screenModel, posDateTimeProvider, sessionDatabase}
    {
    }

    // Screens
    MainScreen mMainScreen;
    MenuScreen mMenuScreen;

    // Screen Models
    MenuScreenModel mMenuModel;
    MainScreenModel mMainScreenModel;
};

ScreenModel::ScreenModel(LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                         LaptimerCore::Positioning::IPositionDateTimeProvider &posDateTimeProvider,
                         LaptimerCore::Session::ISessionDatabase &sessionDatabase)
    : mD{std::make_unique<ScreenModelPrivate>(*this, gpsInfoProvider, posDateTimeProvider, sessionDatabase)}
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
