#ifndef SESSIONVIEWMODEL_HPP
#define SESSIONVIEWMODEL_HPP

#include "CloseCommand.hpp"
#include "LapModel.hpp"
#include "MenuEntry.hpp"
#include "NavigatableModel.hpp"
#include "TableView.hpp"
#include <ISessionDatabase.hpp>
#include <kdbindings/property.h>

class SessionViewModel final : public MenuEntry, public NavigatableModel
{
public:
    SessionViewModel(LaptimerCore::Session::ISessionDatabase &sessionDb);
    ~SessionViewModel();

    /**
     * This is called by the SessionView when the previous session shall be displayed.
     */
    void handleNavigationUp();

    /**
     * This is called by the SessionView when the next session shall be displayed.
     */
    void handleNavigationDown();

    /**
     * This is called by the SessionView when the LapView shall be called.
     */
    void open() override;

    /**
     * This is called by LapView Instance when it should be closed and the
     * SessionView shall be displayed again.
     */
    void close() override;

    /**
     * Property for the session view with the track name of the session.
     */
    KDBindings::Property<std::string> trackName;

    /**
     * Property for the session view with the date of the session.
     */
    KDBindings::Property<std::string> date;

    /**
     * Property for the session view with the lap count of the session.
     */
    KDBindings::Property<std::string> laps;

    /**
     * * Property for the session view with start time of the session.
     */
    KDBindings::Property<std::string> time;

    /**
     * Property for the session view with best lap of the session.
     */
    KDBindings::Property<std::string> bestlap;

    /**
     * This property is the session count indicator.
     */
    KDBindings::Property<std::string> sessionIndicator;

private:
    void displaySession(std::size_t index);

private:
    LaptimerCore::Session::ISessionDatabase &mSessionDb;
    LapModel mLapModel;
    TableView mLapView;
    CloseCommand mLapViewCloseCommand;
};

#endif // SESSIONVIEWMODEL_HPP
