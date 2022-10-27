#ifndef SESSIONVIEWMODEL_HPP
#define SESSIONVIEWMODEL_HPP

#include "MenuEntry.hpp"
#include "NavigatableModel.hpp"
#include <ISessionDatabase.hpp>
#include <kdbindings/property.h>

class SessionViewModel final : public MenuEntry, public NavigatableModel
{
public:
    SessionViewModel(LaptimerCore::Session::ISessionDatabase &sessionDb);
    ~SessionViewModel();

    /**
     *
     */
    void handleNavigationUp();

    /**
     *
     */
    void handleNavigationDown();

    /**
     *
     */
    KDBindings::Property<std::string> trackName;
    /**
     *
     */
    KDBindings::Property<std::string> date;
    /**
     *
     */
    KDBindings::Property<std::string> laps;
    /**
     *
     */
    KDBindings::Property<std::string> time;
    /**
     *
     */
    KDBindings::Property<std::string> bestlap;

    /**
     *
     */
    KDBindings::Property<std::string> sessionIndicator;

private:
    void displaySession(std::size_t index);

private:
    LaptimerCore::Session::ISessionDatabase &mSessionDb;
};

#endif // SESSIONVIEWMODEL_HPP
