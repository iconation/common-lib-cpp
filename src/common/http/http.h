#pragma once

#include <curl/curl.h>
#include <string>

namespace ICONation::Common::Http
{
    class Client
    {
        // Allocators
        public:
            Client (void);
            ~Client (void);

        // HTTP Methods
        public:
            void get (const std::string &url, std::string &out);
            std::string post (const std::string &url, const std::string &params);

        // CURL
        private:
            void init (void);
            void cleanup (void);
            CURL *m_curl;
    };
}