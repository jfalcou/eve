##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

apt-get update && sudo apt-get install -y $COMPILER_PACKAGE
apt-get update && sudo apt-get install -y qemu-user
apt-get update && sudo apt-get install -y qemu
