#pragma once

#include <string>
#include <memory>

namespace ICONation::Common::Application
{
class Application
{
    // Allocators
public:
    Application(int argc, char **argv);
    virtual ~Application(void) = default;

    // Binary name
public:
    std::string binary_name(void) { return m_binary_name; };

protected:
    std::string m_binary_name;

    // Main loop
public:
    int run(void);

private:
    virtual int main(void) = 0;

    // Usage
public:
    virtual void print_usage(void) = 0;
};
} // namespace ICONation::Common::Application