#!/bin/bash

#!/bin/bash

g++ -std=c++20 -Wall -Wextra -Wpedantic -Iinclude \
    $(find src -name "*.cpp") \
    -o app
