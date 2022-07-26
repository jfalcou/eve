#!/bin/sh -l
set -e

compile_target()
{
  echo "::group::Compiling $1" ;
  ninja -v $1 -j $2;
  compile=$?;
  echo "::endgroup::" ;

  return $compile;
}

compile_targets()
{
  for i in `../cmake/toolchain/filter.sh $1 keys`;
  do
  compile_target $i $2;
  if [ "$?" -ne "0" ]
  then
    return 1;
  fi
  done;

  return 0;
}

test_target()
{
  echo "::group::Running $1 tests" ;
  ctest --output-on-failure -R $1 -j $2;
  tested=$?;
  echo "::endgroup::" ;

  return $tested;
}

test_targets()
{
  for i in `../cmake/toolchain/filter.sh $1 values`;
  do
    test_target $i $2;
    if [ "$?" -ne "0" ]
    then
      return 1;
    fi
  done;

  return 0;
}

echo "::group:: Running: '$6 .. -G Ninja -DCMAKE_CXX_FLAGS="$1" $2'"
mkdir build
cd build
$6 .. -G Ninja -DEVE_OPTIONS="$1" $2
echo "::endgroup::"

if [ "$3" -eq "1" ]
then
  echo "::group:: Compiling Unit Tests"
  ninja -v unit -j $4
  echo "::endgroup::"

  echo "::group:: Running Unit Tests"
  ctest --output-on-failure -j $4
  echo "::endgroup::"
else
  echo "::group:: Compiling Unit Tests"
  compile_targets ../cmake/toolchain/$5 $4
  echo "::endgroup::"

  echo "::group:: Running Unit Tests"
  test_targets    ../cmake/toolchain/$5 $4
  echo "::endgroup::"
fi;

exit 0
