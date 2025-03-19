#!/bin/sh
##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

if [ -z "$1" ]; then
    base_dir=$(git rev-parse --show-toplevel)
    llvm-profdata merge -o $base_dir/build/merged.profdata $base_dir/build/unit/profraw.d/*.profraw
else
    llvm-profdata merge -o $1/merged.profdata $1/unit/profraw.d/*.profraw
fi
