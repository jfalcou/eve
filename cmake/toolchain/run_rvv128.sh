#!/bin/sh
##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

qemu-riscv64 --cpu rva23u64,zfh=false,zfhmin=false,zvfh=false,zvfhmin=false,vlen=128 $@
