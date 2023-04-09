#ifndef __MAINSCREENVIEW__H__
#define __MAINSCREENVIEW__H__

#include "ICommand.hpp"
#include "View.hpp"

class MainScreenView : public View
{
public:
    void handleEnter() final;

    void setShowMenuScreenCommand(ICommand *command);

protected:
    ICommand *mNavigateMenuCommand;
};

#endif //!__MAINSCREENVIEW__H__
