#ifndef __IOPENCLOSEHANDLER__H__
#define __IOPENCLOSEHANDLER__H__

class IOpenCloseHandler
{
public:
    virtual void open() = 0;

    virtual void close() = 0;
};

#endif //!__IOPENCLOSEHANDLER__H__