#!/bin/sh -l

compile_target()
{
  echo "::group::Compiling $1" ;
  ninja -v $1 -j 16;
  compile=$?;
  echo "::endgroup::" ;

  return $compile;
}

compile_targets()
{
  for i in `../cmake/toolchain/filter.sh $1 keys`;
  do
  compile_target $i;
  if [ "$?" -ne "0" ]
  then
    echo "::error $i can not be compiled!" ;
    return 1;
  fi
  done;

  return 0;
}

test_target()
{
  echo "::group::Running $1 tests" ;
  ctest --output-on-failure -R $1 -j 16;
  tested=$?;
  echo "::endgroup::" ;

  return $tested;
}

test_targets()
{
  for i in `../cmake/toolchain/filter.sh $1 values`;
  do
    test_target $i;
    if [ "$?" -ne "0" ]
    then
      echo "::error $i tests failed!" ;
      return 1;
    fi
  done;

  return 0;
}

echo "::group::Running: 'cmake .. -G Ninja -DEVE_OPTIONS="$1" $2'"
mkdir build
cd build
cmake .. -G Ninja -DEVE_OPTIONS="$1" $2
echo "::endgroup::"

compile_targets ../cmake/toolchain/arch.targets.json
if [ "$?" -eq "1" ]
then
  exit 1;
fi

test_targets    ../cmake/toolchain/arch.targets.json
if [ "$?" -eq "1" ]
then
  exit 1;
fi

compile_targets ../cmake/toolchain/api.targets.json
if [ "$?" -eq "1" ]
then
  exit 1;
fi

test_targets    ../cmake/toolchain/api.targets.json
if [ "$?" -eq "1" ]
then
  exit 1;
fi

if [ "$3" -eq "1" ]
then

  compile_targets ../cmake/toolchain/doc.targets.json
  if [ "$?" -eq "1" ]
  then
    exit 1;
  fi

  test_targets    ../cmake/toolchain/doc.targets.json
  if [ "$?" -eq "1" ]
  then
    exit 1;
  fi

  compile_targets ../cmake/toolchain/real.targets.json
  if [ "$?" -eq "1" ]
  then
    exit 1;
  fi

  test_targets    ../cmake/toolchain/real.targets.json
  if [ "$?" -eq "1" ]
  then
    exit 1;
  fi
fi

exit 0
