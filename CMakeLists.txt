cmake_minimum_required (VERSION 3.0)
project (COMMON_LIB_CPP)

# === GLOBAL ====================================================================================================
# Directories
set (ROOTDIR ${PROJECT_SOURCE_DIR})
set (LIBDIR ${ROOTDIR}/lib/${CMAKE_ARCHITECTURE}/)
set (RELEASE_DIR ${ROOTDIR}/release/${CMAKE_ARCHITECTURE}/)
set (VCPKG_ROOT $ENV{VCPKG_ROOT})

# Includes
include_directories (${ROOTDIR}/third_party)
if (MSVC)
    # VCPKG directories on Windows
    include_directories (${VCPKG_ROOT}/installed/${CMAKE_ARCHITECTURE}-windows/include/)
endif (MSVC)

# CMAKE Configs
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RELEASE_DIR})
if (MSVC)
    set (CMAKE_CXX_FLAGS_RELEASE "/std:c++17 /MD /O2")
    set (CMAKE_CXX_FLAGS_DEBUG "/std:c++17 /MDd /Od /Zi")
else ()
    # Assume g++
    set (CMAKE_CXX_FLAGS_RELEASE "-std=c++17 -O2")
    set (CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -g")
endif (MSVC)

# === Common =======================================================================================================
# Directories
set (COMMON_ROOT ${ROOTDIR})
set (COMMON_SRCDIR ${COMMON_ROOT}/src/)

# SPDLOG defines
add_definitions (-DSPDLOG_FMT_EXTERNAL)
add_definitions (-DFMT_HEADER_ONLY)

# Common source code
file (GLOB_RECURSE COMMON_SRC
    ${COMMON_SRCDIR}/*.cpp     ${COMMON_SRCDIR}/*.h
)

# Common library
add_library (common_lib STATIC ${COMMON_SRC})
target_include_directories (common_lib PRIVATE ${COMMON_SRCDIR})
target_link_libraries (common_lib ${MYSQL_LIBRARIES} ${CURL_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
