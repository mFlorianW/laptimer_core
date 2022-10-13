#ifndef __NAVIGATEBLEMODEL__H__
#define __NAVIGATEBLEMODEL__H__

#include <cstdint>

class NavigatableModel
{
public:
    virtual ~NavigatableModel() = default;

protected:
    NavigatableModel(std::size_t size);

    void setSize(std::size_t size);
    std::size_t getIndex() const;

    void incrementIndex();
    void decrementIndex();

private:
    std::size_t mIndex{0};
    std::size_t mSize{0};
};

#endif //!__NAVIGATEBLEMODEL__H__