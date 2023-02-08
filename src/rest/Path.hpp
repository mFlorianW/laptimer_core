#pragma once
#include <SharedDataPointer.hpp>
#include <optional>
#include <string>

namespace LaptimerCore::Rest
{
class SharedPath;

/**
 * A path in a REST URL and provide access to the
 * elements in the URL.
 */
class Path final
{
public:
    /**
     * Creates an instance of the path.
     * @param path The that shall be used.
     */
    Path(std::string path) noexcept;

    /**
     * Empty default destructor
     */
    ~Path() noexcept;

    /**
     * Copy constructor for Path
     * @param ohter The object to copy from.
     */
    Path(const Path &ohter);

    /**
     * The copy assignment operator for Path.
     * @param other The object to copy from.
     * @return Path& A reference to the copied path.
     */
    Path &operator=(const Path &other);

    /**
     * Move constructor for Path
     * @param other The object to move from.
     */
    Path(Path &&other);

    /**
     * The move assignment operator for the Path.
     * @param other The object to move from.
     * @return Path& A reference to the moved path.
     */
    Path &operator=(Path &&other);

    /**
     * Gives the depth of the path.
     * @return The depth of the path
     */
    std::size_t getDepth() const noexcept;

    /**
     * Gives the entry by the index when the index is not valid an
     * nullopt will be returned.
     * @return The entry or an invalid index if the is not present.
     */
    std::optional<std::string_view> getEntry(std::size_t index) const noexcept;

private:
    Common::SharedDataPointer<SharedPath> mData;
};
} // namespace LaptimerCore::Rest
