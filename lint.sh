#!/bin/bash
find ${1} -type f \
     -regextype posix-extended -regex '.*\.(cpp|hpp)$' \
     -exec clang-tidy --extra-arg=-Wno-unknown-warning-option --fix -p "${2}" {} \;
