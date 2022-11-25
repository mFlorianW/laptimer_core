#include "MainScreenModel.hpp"

// Setup ActiveSessionView

MainScreenModel::MainScreenModel(ScreenModel &screenModel,
                                 LaptimerCore::Positioning::IPositionDateTimeProvider &posDateTimeProvider,
                                 LaptimerCore::Session::ISessionDatabase &sessionDatabase)
    : mActiveSessionWorkflow{posDateTimeProvider, mLapTimer, sessionDatabase}
    , mScreenModel{screenModel}
    , mTrackDetectionWorkflow{mTrackDetector, posDateTimeProvider}
    , mActiveSessionModel{mTrackDetectionWorkflow, mActiveSessionWorkflow}
    , mShowMenuScreenCommand{mScreenModel}
    , mActiveSessionView{mActiveSessionModel}
{
    mActiveSessionView.setShowMenuScreenCommand(&mShowMenuScreenCommand);
}

View &MainScreenModel::getActiveView()
{
    return mActiveSessionView;
}
