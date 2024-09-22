#!/usr/bin/zsh

g++ src/server.cpp -o server -I ./include
echo 'server.cpp compiled'

g++ src/client.cpp -o client -I ./include
echo 'client.cpp compiled'
