#include "../include/ScreenModel.hpp"
#include "MainScreen.hpp"
#include "MainScreenModel.hpp"
#include "MenuScreen.hpp"
#include "MenuScreenModel.hpp"
#include <lvgl.h>

struct ScreenModelPrivate
{
    explicit ScreenModelPrivate(ScreenModel &screenModel,
                                LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                                LaptimerCore::Positioning::IPositionDateTimeProvider &posDateTimeProvider,
                                LaptimerCore::Session::ISessionDatabase &sessionDatabase,
                                LaptimerCore::TrackManagement::ITrackDatabase &trackDatabase)
        : mMainScreen{gpsInfoProvider}
        , mMenuModel{screenModel, sessionDatabase}
        , mMainScreenModel{screenModel, posDateTimeProvider, sessionDatabase, trackDatabase}
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
                         LaptimerCore::Session::ISessionDatabase &sessionDatabase,
                         LaptimerCore::TrackManagement::ITrackDatabase &trackDatabase)
    : mD{std::make_unique<ScreenModelPrivate>(*this,
                                              gpsInfoProvider,
                                              posDateTimeProvider,
                                              sessionDatabase,
                                              trackDatabase)}
{
    // Connect to menu model view changed
    mD->mMenuModel.viewChanged.connect(&ScreenModel::activateMenuScreen, this);
    mD->mMenuModel.closeMenu.connect(&ScreenModel::activateMainScreen, this);
}

ScreenModel::~ScreenModel() = default;

void ScreenModel::activateMainScreen()
{
    mD->mMenuScreen.setVisible(false);
    auto &mainScreenView = mD->mMainScreenModel.getActiveView();
    mD->mMainScreen.setScreenContent(&mainScreenView);
    lv_scr_load(mD->mMainScreen.getScreen());
}

void ScreenModel::activateMenuScreen()
{
    mD->mMainScreen.setVisible(false);
    auto &menuView = mD->mMenuModel.getActiveView();
    mD->mMenuScreen.setScreenContent(&menuView);
    lv_scr_load(mD->mMenuScreen.getScreen());
}
