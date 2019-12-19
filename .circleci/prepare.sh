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
apt-get update && sudo apt-get install -y wget
apt-get update && sudo apt-get install -y cmake
apt-get update && sudo apt-get install -y ninja-build

wget https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.gz
tar -zxvf boost_1_72_0.tar.gz
cd boost_1_72_0 && ./bootstrap.sh
LOCALBOOST=`pwd`
echo "BOOST INSTALLED AT " $LOCALBOOST
exit 1

if hash "git" 2>/dev/null; then
  git --version;
else
  apt-get update && sudo apt-get install -y git;
fi
