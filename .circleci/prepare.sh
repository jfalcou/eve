##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

apt-get update && apt-get install -y sudo && rm -rf /var/lib/apt/lists/*
sudo apt-get install -y cmake
sudo apt-get install -y ninja-build
sudo apt-get install -y libboost-math-dev

if [[ -v REQUIRES_CLANG ]]
then
  sudo apt-get install -y clang-9
  sudo apt-get install -y libstdc++-9-dev
fi

if hash "git" 2>/dev/null; then
  git --version;
else
  apt-get update && sudo apt-get install -y git;
fi
