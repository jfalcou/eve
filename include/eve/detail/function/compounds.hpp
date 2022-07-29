//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/bit_compounds.hpp>
#include <eve/detail/function/simd/common/arithmetic_compounds.hpp>
#include <eve/detail/function/operators.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/bit_compounds.hpp>
#  include <eve/detail/function/simd/x86/arithmetic_compounds.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/bit_compounds.hpp>
#  include <eve/detail/function/simd/ppc/arithmetic_compounds.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/bit_compounds.hpp>
#  include <eve/detail/function/simd/arm/neon/arithmetic_compounds.hpp>
#endif

#if defined(EVE_INCLUDE_WASM_HEADER)
#  include <eve/detail/function/simd/wasm/bit_compounds.hpp>
#  include <eve/detail/function/simd/wasm/arithmetic_compounds.hpp>
#endif
