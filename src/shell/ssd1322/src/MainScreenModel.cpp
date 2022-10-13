#include "MainScreenModel.hpp"

// Setup ActiveSessionView

MainScreenModel::MainScreenModel(ScreenModel &screenModel,
                                 LaptimerCore::Positioning::IPositionInformationProvider &gpsPositionProvider,
                                 LaptimerCore::Positioning::IPositionDateTimeProvider &posDateTimeProvider,
                                 LaptimerCore::Session::ISessionDatabase &sessionDatabase)
    : mScreenModel{screenModel}
    , mTrackDetectionWorkflow{mTrackDetector, gpsPositionProvider}
    , mActiveSessionWorkflow{posDateTimeProvider, mLapTimer, sessionDatabase}
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
