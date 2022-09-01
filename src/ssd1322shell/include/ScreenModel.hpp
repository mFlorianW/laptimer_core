#ifndef __SCREENCONTROLLER__H__
#define __SCREENCONTROLLER__H__

#include <IGPSInformationProvider.hpp>
#include <IPositionInformationProvider.hpp>
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
                LaptimerCore::Positioning::IPositionInformationProvider &posInfoProvider);

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