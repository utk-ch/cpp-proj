# cpp-proj

# build command

## build part2

change current directory to "part2"

g++ -std=c++2a MereMemo/tests/*.cpp -o main

specify `Test.h` as an external library

g++ -std=c++2a -I/workspaces/cpp-proj/part2 -L/workspaces/cpp-proj/part2 MereMemo/tests/*.cpp -o main

## build part1
g++ -std=c++2a part1/tests/*.cpp -o part1/main

g++ -std=c++17 tests/*.cpp -o main