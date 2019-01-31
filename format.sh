##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/bin/sh
#
# Usage:
#
#  source format.sh <root folder>
#
format_com=clang-format
n=0

for m in `find ${1} -name "*.?pp" ` ; do
        let n++
        echo "$n: Processing " "$m"
        $format_com -i "$m"
        git add "$m"
done

