#include "jsonrpc.h"

using json = nlohmann::json;

namespace ICONation::Common::JsonRPC
{
Client::Client(const std::string &endpoint)
    : m_endpoint(endpoint)
{
}

Client::~Client(void)
{
}

json Client::call(const std::string &method, const json &params)
{
    json request;

    request["jsonrpc"] = "2.0";
    request["id"] = 1234;
    request["method"] = method;

    if (!params.empty())
    {
        request["params"] = params;
    }

    return json::parse(m_http.post(m_endpoint, request.dump()));
}
} // namespace ICONation::Common::JsonRPC