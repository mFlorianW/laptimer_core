#ifndef __ACTIVESESSIONMODEL__H__
#define __ACTIVESESSIONMODEL__H__

#include "ITrackDetectionWorkflow.hpp"
#include "kdbindings/property.h"

class ActiveSessionModel
{
public:
    ActiveSessionModel(LaptimerCore::Workflow::ITrackDetectionWorkflow &trackDetector);

    KDBindings::Property<LaptimerCore::Common::TrackData> detectedTrack;

private:
    LaptimerCore::Workflow::ITrackDetectionWorkflow &mTrackDetector;
};

#endif //!__ACTIVESESSIONMODEL__H__