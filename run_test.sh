##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/bin/bash
#
# Usage:
#
#  source run_test.sh <build folder> <test ID>
#
target=$1
test=$2

echo "test : ${test} on ${target}"

echo "*******************************************"
cd ./build/$target
ninja -j 4 $test.unit
ctest -j 4 -R ^$test.*.unit
cd ../..

