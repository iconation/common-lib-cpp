#include "base64.h"
#include "common/exception/exception.h"
#include <openssl/evp.h>

namespace ICONation::Common::Crypto
{
    static size_t base64_size (size_t nBytes)
    {
        return ((4 * nBytes / 3) + 3) & ~3;
    }

    static size_t output_size (const std::string &input)
    {
        int y = 0;

        if (input.at (input.size() - 1) == '=') {
            y++;
            if (input.at (input.size() - 2) == '=') {
                y++;
            }
        
        }

        return (3 * input.size() / 4) - 1;
    }

    std::string Base64::encode (const std::vector<unsigned char> &in)
    {
        // Get output size
        size_t outSize = base64_size (in.size());
        std::string out;
        out.resize (outSize);

        int encodedSize;
        if ((encodedSize = EVP_EncodeBlock ((unsigned char *) out.data(), &in[0], (int) in.size())) == -1) {
            throw Common::Exception::OpenSSLError ("EVP_EncodeBlock failed.");
        }

        if (encodedSize != out.size()) {
            throw Common::Exception::InvalidSize (out, encodedSize);
        }

        return out;
    }

    std::vector<unsigned char> Base64::decode (const std::string &in)
    {
        // Get output size
        size_t outSize = output_size (in);
        std::vector<unsigned char> out (outSize);

        if (EVP_DecodeBlock (&out[0], (const unsigned char *) in.c_str(), (int) in.size()) == -1) {
            throw Common::Exception::OpenSSLError ("EVP_DecodeBlock failed.");
        }

        return out;
    }
}