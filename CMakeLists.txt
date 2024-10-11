cmake_minimum_required(VERSION 3.10)

# Project Name
project(GChain)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(gchain ${SOURCES})

# Find OpenSSL for cryptographic functions
find_package(OpenSSL REQUIRED)
if(OpenSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(gchain PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

# Find Boost libraries (if needed later)
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(gchain PRIVATE Boost::system)
endif()