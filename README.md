## Install macOS

# Install Homebrew
- /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
- brew install wget

# BOOST
- brew install boost

## Instal linux
- sudo apt-get install libboost-all-dev 
- sudo apt-get install g++

## Build
- g++ server.cpp -o server -lboost_system
- ./server

- g++ client.cpp -o client –lboost_system
- ./client

## Overview
https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/overview.html