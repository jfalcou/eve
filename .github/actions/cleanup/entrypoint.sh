#!/bin/sh -l

echo "::group::Cleaning external files"
rm -rf build/
echo "::endgroup::"
return 0;
