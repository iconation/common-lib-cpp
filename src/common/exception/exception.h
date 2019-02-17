#pragma once

#include <exception>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <openssl/err.h>

namespace ICONation::Common::Exception
{
    struct Unimplemented : public std::runtime_error
    {
        Unimplemented (const std::string &message) throw()
        :   std::runtime_error (message) {}
        virtual char const *what (void) const throw() { return exception::what(); }
    };
    
    struct OpenSSLError : public std::runtime_error {
        OpenSSLError (const std::string &message) throw() : 
            std::runtime_error (fmt::format ("{} : {}", message, ERR_error_string (ERR_get_error(), NULL))) {}
    };
    
    struct InvalidSize : public std::runtime_error {
        InvalidSize (const std::string &data, size_t expectedSize) throw() : 
            std::runtime_error (fmt::format ("'{}' : size is '{}', should be '{}'", 
                data, data.size(), expectedSize)) {}
        InvalidSize (const std::vector<unsigned char> &data, size_t expectedSize) throw() : 
            std::runtime_error (fmt::format ("'{}' : size is '{}', should be '{}'", 
                &data[0], data.size(), expectedSize)) {}
        InvalidSize (size_t actualSize, size_t expectedSize) throw() : 
            std::runtime_error (fmt::format ("Size is '{}', should be '{}'", 
                actualSize, expectedSize)) {}
    };
    
    struct InternalError : public std::runtime_error
    {
        InternalError (const std::string &message) throw()
        :   std::runtime_error (message) {}
        virtual char const *what (void) const throw() { return exception::what(); }
    };
}