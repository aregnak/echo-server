#!/usr/bin/zsh

g++ src/server.cpp -o server
echo 'server.cpp compiled'

g++ src/client.cpp -o client
echo 'client.cpp compiled'
