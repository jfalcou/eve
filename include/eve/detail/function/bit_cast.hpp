//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(bit_cast_, bit_cast);
}

#include <eve/detail/function/simd/common/bit_cast.hpp>

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/bit_cast.hpp>
#endif
