#ifndef __MAINSCREENMODEL__H__
#define __MAINSCREENMODEL__H__

#include "ActiveSessionModel.hpp"
#include "ActiveSessionView.hpp"
#include "IGPSInformationProvider.hpp"
#include "ShowMenuScreenCommand.hpp"
#include "TrackDetection.hpp"
#include "TrackDetectionWorkflow.hpp"

class ScreenModel;
class MainScreenModel
{
public:
    MainScreenModel(ScreenModel &screenModel,
                    LaptimerCore::Positioning::IPositionInformationProvider &gpsPositionProvider);
    View &getActiveView();

private:
    // Backends
    LaptimerCore::Algorithm::TrackDetection mTrackDetector{500};

    // Models
    ScreenModel &mScreenModel;
    LaptimerCore::Workflow::TrackDetectionWorkflow mTrackDetectionWorkflow;
    ActiveSessionModel mActiveSessionModel;

    // Commands
    ShowMenuScreenCommand mShowMenuScreenCommand;

    // Views
    ActiveSessionView mActiveSessionView;
};

#endif //!__MAINSCREENMODEL__H__