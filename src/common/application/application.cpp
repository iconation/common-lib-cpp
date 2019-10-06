#include "application.h"
#include "common/dbg/dbg.h"
#include <cstdlib>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace ICONation::Common::Application
{
Application::Application(int argc, char **argv)
{
    // Read command line
    m_binary_name = fs::path(argv[0]).filename().string();
}

int Application::run(void)
{
    try
    {
        print_usage();
        return main();
    }
    catch (const std::exception &e)
    {
        Common::Dbg::error("Application exception :");
        Common::Dbg::error("    - Type   : {}", typeid(e).name());
        Common::Dbg::error("    - Reason : {}", e.what());
        return -1;
    }
}
} // namespace ICONation::Common::Application