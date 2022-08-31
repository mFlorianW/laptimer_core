#ifndef __ICOMMAND__H__
#define __ICOMMAND__H__

class ICommand
{
public:
    virtual ~ICommand() = default;

    /**
     * Execute the commands.
     */
    virtual void execute() = 0;
};

#endif //!__ICOMMAND__H__