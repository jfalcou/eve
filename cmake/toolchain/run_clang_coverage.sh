#!/bin/sh
##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

mkdir -p profraw.d

base_name=$(basename "$1")
base_name="${base_name%.*}"

LLVM_PROFILE_FILE="profraw.d/${base_name}.profraw" $@
