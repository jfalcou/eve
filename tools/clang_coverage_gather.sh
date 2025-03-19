#!/bin/sh
##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

if [ -z "$1" ]; then
  wdir="build"
else
  wdir=$1
fi

# merge all .profraw files into a single .profdata file
llvm-profdata merge -o $wdir/merged.profdata $wdir/unit/profraw.d/*.profraw

object_files=$(find $wdir -type f -name "*.o" -path "*unit.*")
object_files_arg=""
for obj_file in $object_files; do
  object_files_arg="$object_files_arg --object $obj_file"
done

# convert the .profraw file into a .lcov file
llvm-cov export -format=lcov -instr-profile $wdir/merged.profdata $object_files_arg > $wdir/merged.lcov
