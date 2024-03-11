#include "MainScreenModel.hpp"

// Setup ActiveSessionView

MainScreenModel::MainScreenModel(ScreenModel& screenModel,
                                 LaptimerCore::Positioning::IPositionDateTimeProvider& posDateTimeProvider,
                                 LaptimerCore::Storage::ISessionDatabase& sessionDatabase,
                                 LaptimerCore::Storage::ITrackDatabase& trackDatabase)
    : mActiveSessionWorkflow{posDateTimeProvider, mLapTimer, sessionDatabase}
    , mScreenModel{screenModel}
    , mTrackDetectionWorkflow{mTrackDetector, posDateTimeProvider}
    , mActiveSessionModel{mTrackDetectionWorkflow, mActiveSessionWorkflow, trackDatabase}
    , mShowMenuScreenCommand{mScreenModel}
    , mActiveSessionView{mActiveSessionModel}
{
    mActiveSessionView.setShowMenuScreenCommand(&mShowMenuScreenCommand);
}

View& MainScreenModel::getActiveView()
{
    return mActiveSessionView;
}
