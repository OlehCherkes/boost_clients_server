## Install macOS

# Install Homebrew
- /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
- brew install wget

# BOOST
- brew install boost

## Instal linux
- sudo apt-get install libboost-all-dev 
- sudo apt-get install g++

## Build sync
- g++ server.cpp -o server -lboost_system
- ./server

- g++ client.cpp -o client –lboost_system
- ./client

## Build async
- g++ async_server.cpp -o async_server –lboost_system
- ./async_server
- 
## Bind
void print(int x, int y)
{
    std::cout << x << " " << y << std::endl;
}

auto bound_function = boost::bind(&print, 42, _1);
bound_function(10);

## Overview
https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/overview.html
https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T