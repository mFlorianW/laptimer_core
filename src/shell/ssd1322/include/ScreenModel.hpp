#ifndef __SCREENCONTROLLER__H__
#define __SCREENCONTROLLER__H__

#include "IPositionDateTimeProvider.hpp"
#include <IGPSInformationProvider.hpp>
#include <ISessionDatabase.hpp>
#include <ITrackDatabase.hpp>
#include <memory>

/**
 * ScreenModel setups the Shell
 */
struct ScreenModelPrivate;
class ScreenModel
{
public:
    /**
     * Creates an Instance of the ScreenModel
     * @param gpsInfoProvider The GPS information provider service.
     * @param posInfoProvider  The GPS position information provider service.
     */
    ScreenModel(LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                LaptimerCore::Positioning::IPositionDateTimeProvider &posDateTimeProvider,
                LaptimerCore::Storage::ISessionDatabase &sessionDatabase,
                LaptimerCore::Storage::ITrackDatabase &trackDatabase);

    virtual ~ScreenModel();

    /**
     * Activates the mainScreen view
     */
    void activateMainScreen();

    /**
     * Activates the menu screen
     */
    void activateMenuScreen();

private:
    std::unique_ptr<ScreenModelPrivate> mD;
};

#endif //!__SCREENCONTROLLER__H__
