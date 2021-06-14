#!/bin/bash
echo "Formatting code"
find include/ -name *.cpp -or -name *.hpp | xargs clang-format -i
find src/ -name *.cpp -or -name *.hpp | xargs clang-format -i
find test/ -name *.cpp -or -name *.hpp | xargs clang-format -i
