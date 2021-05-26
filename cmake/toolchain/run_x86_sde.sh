##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/bin/sh

lscpu | grep "avx512";
check=$?

echo "Status of AVX512 : ${check} - ${@}"

if [ "${check}" -eq "0" ]
then
  sde64 -- $@
else
  $@
fi
