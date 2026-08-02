#!/bin/sh
##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

qemu-riscv64 --cpu rva23u64,zfh=true,zfhmin=true,zvfh=true,zvfhmin=true,vlen=256 $@
