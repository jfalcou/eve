##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

mkdir -p build
cd build

if [[ -v RUN_COMMAND ]]
then
  echo "Running tests with $RUN_COMMAND ..."
  cmake .. -G Ninja -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS" -DCMAKE_CROSSCOMPILING_CMD="$RUN_COMMAND"
else
  cmake .. -G Ninja -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS"
fi

if [[ -v EXTRA_PATH ]]
then
  echo "Updating path for $EXTRA_PATH/$EXTRA_NAME ..."
  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$EXTRA_PATH
  export LD_LIBRARY_PATH
  ln -s $EXTRA_PATH/$EXTRA_NAME /$EXTRA_LIB/$EXTRA_NAME
fi

echo "ninja $TARGET.unit -j $REPLICATION"
ninja $TARGET.unit -j $REPLICATION

echo "ctest -R $TARGET.*.unit -j 8"

if [ "$TARGET" == "basic" ]
then
  ctest -R ^arch.*.unit -j 8
  ctest -R ^doc.*.unit  -j 8
  ctest -R ^api.*.unit  -j 8
elif
  ctest -R $TARGET.*.unit -j 8
fi
