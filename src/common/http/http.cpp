#include "http.h"
#include "exception.h"
#include "common/dbg/dbg.h"

namespace ICONation::Common::Http
{
Client::Client(void)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    m_curl = nullptr;
}

Client::~Client(void)
{
    curl_global_cleanup();
}

static size_t writeCallback(char *contents, size_t size, size_t nmemb, std::string *outBuffer)
{
    outBuffer->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void Client::get(const std::string &url, std::string &out)
{
    init();

    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    // curl_easy_setopt (m_curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &out);

    CURLcode res = curl_easy_perform(m_curl);

    if (res != CURLE_OK)
    {
        throw Http::Exception::CurlError(url, res);
    }

    cleanup();
}

void Client::init(void)
{
    m_curl = curl_easy_init();
}

void Client::cleanup(void)
{
    curl_easy_cleanup(m_curl);
    m_curl = nullptr;
}

std::string Client::post(const std::string &url, const std::string &params)
{
    std::string out;

    init();
    // Common::Dbg::info ("Posting {}", params);

    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, params.c_str());
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &out);

    CURLcode res = curl_easy_perform(m_curl);

    if (res != CURLE_OK)
    {
        throw Http::Exception::CurlError(url, res);
    }

    cleanup();
    return out;
}
} // namespace ICONation::Common::Http