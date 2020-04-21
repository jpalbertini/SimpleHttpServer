#ifndef SIMPLEHTTPSERVER_TYPES
#define SIMPLEHTTPSERVER_TYPES

#include <optional>
#include <functional>

#include "SimpleHttpServer/serverresponse.hpp"

class ServerResponse;
namespace shs
{
    using CallbackResponse = std::optional<ServerResponse>;

    struct QueryInformations;
    using GetFuntion = std::function<CallbackResponse(const QueryInformations& requestHeaders)>;
}

#endif //SIMPLEHTTPSERVER_TYPES