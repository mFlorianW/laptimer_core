#include "MainScreenModel.hpp"

// Setup ActiveSessionView

MainScreenModel::MainScreenModel(ScreenModel &screenModel,
                                 LaptimerCore::Positioning::IPositionInformationProvider &gpsPositionProvider)
    : mScreenModel{screenModel}
    , mTrackDetectionWorkflow{mTrackDetector, gpsPositionProvider}
    , mActiveSessionModel{mTrackDetectionWorkflow}
    , mShowMenuScreenCommand{mScreenModel}
    , mActiveSessionView{mActiveSessionModel}
{
    mActiveSessionView.setShowMenuScreenCommand(&mShowMenuScreenCommand);
}

View &MainScreenModel::getActiveView()
{
    return mActiveSessionView;
}
