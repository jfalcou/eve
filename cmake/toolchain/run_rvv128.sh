##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
#!/bin/sh

qemu-riscv64 --cpu rv64,v=true,vlen=128 $@
