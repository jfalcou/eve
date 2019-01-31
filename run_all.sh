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
#  source run_all.sh
#
for i in `ls build`
do
  echo ${i}
  echo "*******************************************"
  cd ./build/$i
  ninja -j 4 unit
  ctest -j 4
  cd ../..
done

