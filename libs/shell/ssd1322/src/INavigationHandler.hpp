#ifndef __INAVIGATIONHANDLER__H__
#define __INAVIGATIONHANDLER__H__

class INavigationHandler
{
public:
    virtual ~INavigationHandler() = default;

    /**
     * Handle down navigation
     */
    virtual void navigateDown() = 0;

    /**
     * Handle up navigation
     */
    virtual void navigateUp() = 0;
};

#endif //!__INAVIGATIONHANDLER__H__