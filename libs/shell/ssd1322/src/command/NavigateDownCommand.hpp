#ifndef __NAVIGATEDOWNCOMMAND__H__
#define __NAVIGATEDOWNCOMMAND__H__

#include "ICommand.hpp"
#include "INavigationHandler.hpp"

class NavigateDownCommand : public ICommand
{
public:
    NavigateDownCommand(INavigationHandler& handler);

    void execute() override;

private:
    INavigationHandler& mHandler;
};

#endif //!__NAVIGATEDOWNCOMMAND__H__