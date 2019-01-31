##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/bin/bash
# Usage:
#
#  source run_tests.sh <test ID>
#
test=$1

for i in `ls build`
do
  ./run_test.sh ${i} ${test}
done

