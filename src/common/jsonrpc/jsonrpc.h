#pragma once

#include <nlohmann/json.hpp>
#include "common/http/http.h"

namespace ICONation::Common::JsonRPC
{
    class Client
    {
        // Allocators
        public:
            Client (const std::string &endpoint);
            ~Client (void);

        // Commands
        public:
            nlohmann::json call (const std::string &method, const nlohmann::json &params);

        // Http Client
        private:
            std::string m_endpoint;
            Http::Client m_http;
    };
}