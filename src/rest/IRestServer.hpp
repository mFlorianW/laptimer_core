#pragma once

#include "IRestRequestHandler.hpp"

namespace LaptimerCore::Rest
{
enum ServerStartResult
{
    Ok,
    Error
};

enum class PostHandler
{
    PositionHandler,
};

enum class GetHandler
{
    SessionHandler,
};

class IRestServer
{
public:
    /**
     * Default Destructor
     */
    virtual ~IRestServer() = default;

    /**
     * Deleted copy constructor.
     */
    IRestServer(const IRestServer &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    IRestServer &operator=(const IRestServer &other) = delete;

    /**
     * Deleted move constructor
     */
    IRestServer(IRestServer &&other) = delete;

    /**
     * Deleted move assignment operator
     */
    IRestServer &operator=(const IRestServer &&other) = delete;

    /**
     * Starts the REST server.
     * @return ServerStartResult::Ok Server successful started.
     * @return ServerStartResult::Error Failed to start the server, something somewhere went wrong.
     */
    [[nodiscard]] virtual ServerStartResult start() noexcept = 0;

    /**
     * Stops the REST server
     */
    virtual void stop() noexcept = 0;

    /**
     * Registers a POST method handler in the server. The handler is called when a request for the registered type is
     * received. The server can only have one handle for each type at the time. The last set handle for a type is called
     * by the server.
     *
     * @note
     * The Server doesn't take any ownership about the handler object. The caller must guarantee that object lives as
     * long as the server.
     *
     * @param type The type to register the handler.
     * @param handler The handler object that is called when the type receives a request.
     */
    virtual void registerPostHandler(PostHandler type, IRestRequestHandler *handler) noexcept = 0;

    /**
     * Registers a GET method handler in the server. The handler is called when a request for the registered type is
     * received. The Server can only have on handler for each type at the time. The last set handler for a type is
     * called by the server.
     *
     * @note
     * The Server doesn't take any ownership about the handler object. The caller must guarantee that object lives as
     * long as the server.
     *
     * @param type The type to register the handler.
     * @param handler The handler object that is called when the type receives a request.
     */
    virtual void registerGetHandler(GetHandler type, IRestRequestHandler *handler) noexcept = 0;

protected:
    IRestServer() = default;
};
} // namespace LaptimerCore::Rest
