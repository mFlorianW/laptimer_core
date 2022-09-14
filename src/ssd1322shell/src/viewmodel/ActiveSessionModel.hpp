#ifndef __ACTIVESESSIONMODEL__H__
#define __ACTIVESESSIONMODEL__H__

#include <IActiveSessionWorkflow.hpp>
#include <ITrackDetectionWorkflow.hpp>
#include <kdbindings/property.h>

class ActiveSessionModel
{
public:
    ActiveSessionModel(LaptimerCore::Workflow::ITrackDetectionWorkflow &trackDetector,
                       LaptimerCore::Workflow::IActiveSessionWorkflow &activeWorkSessionFlow);

    KDBindings::Property<LaptimerCore::Common::TrackData> detectedTrack;

private:
    LaptimerCore::Workflow::ITrackDetectionWorkflow &mTrackDetector;
    LaptimerCore::Workflow::IActiveSessionWorkflow &mActiveWorkSessionFlow;
};

#endif //!__ACTIVESESSIONMODEL__H__
