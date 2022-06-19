#!/bin/sh -l

compile_target()
{
  echo "::group::Compiling Unit Tests" ;
  ninja -v unit -j 8;
  compile=$?;
  echo "::endgroup::" ;

  return $compile;
}

test_target()
{
  echo "::group::Running Unit Tests" ;
  ctest --output-on-failure -R ^unit.*.exe -j 8;
  tested=$?;
  echo "::endgroup::" ;

  return $tested;
}

echo "::group::Running: 'cmake .. -G Ninja -DEVE_OPTIONS="$1" $2'"
mkdir build
cd build
cmake .. -G Ninja -DEVE_OPTIONS="$1" $2
echo "::endgroup::"

compile_target
if [ "$?" -eq "1" ]
then
  exit 1;
fi

test_target
if [ "$?" -eq "1" ]
then
  exit 1;
fi

exit 0
