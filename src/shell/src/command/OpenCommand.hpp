#ifndef __OPENCOMMAND__H__
#define __OPENCOMMAND__H__

#include "ICommand.hpp"
#include "IOpenCloseHandler.hpp"

class OpenCommand : public ICommand
{
public:
    /**
     *
     * @param handler
     */
    OpenCommand(IOpenCloseHandler &handler);

    void execute() override;

private:
    IOpenCloseHandler &mHandler;
};

#endif //!__OPENCOMMAND__H__