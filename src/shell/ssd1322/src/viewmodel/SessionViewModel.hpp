#ifndef SESSIONVIEWMODEL_HPP
#define SESSIONVIEWMODEL_HPP

#include <ISessionDatabase.hpp>
#include <kdbindings/property.h>
#include "NavigatableModel.hpp"

class SessionViewModel final : public NavigatableModel
{
public:
    SessionViewModel(LaptimerCore::Session::ISessionDatabase &sessionDb);
    ~SessionViewModel();

    void handleNavigationUp();

    void handleNavigationDown();

    KDBindings::Property<std::size_t> sessionCount;

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

private:
    void displaySession(std::size_t index);

private:
    LaptimerCore::Session::ISessionDatabase &mSessionDb;
};

#endif // SESSIONVIEWMODEL_HPP
