#ifndef __MAINSCREENMODEL__H__
#define __MAINSCREENMODEL__H__

#include "ActiveSessionModel.hpp"
#include "ActiveSessionView.hpp"
#include "ShowMenuScreenCommand.hpp"
#include <ActiveSessionWorkflow.hpp>
#include <IPositionDateTimeProvider.hpp>
#include <SimpleLaptimer.hpp>
#include <TrackDetection.hpp>
#include <TrackDetectionWorkflow.hpp>

class ScreenModel;
class MainScreenModel
{
public:
    MainScreenModel(ScreenModel &screenModel,
                    LaptimerCore::Positioning::IPositionDateTimeProvider &posDateTimeProvider,
                    LaptimerCore::Session::ISessionDatabase &sessionDatabase,
                    LaptimerCore::Storage::ITrackDatabase &trackDatabase);
    View &getActiveView();

private:
    // Backends
    LaptimerCore::Algorithm::TrackDetection mTrackDetector{500};
    LaptimerCore::Algorithm::SimpleLaptimer mLapTimer;

    // ActiveSessionBackend
    LaptimerCore::Workflow::ActiveSessionWorkflow mActiveSessionWorkflow;

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
