//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/native_shuffle_helpers.hpp>

namespace eve
{

// level4 and level5 combine up to 2 instructions

EVE_REGISTER_CALLABLE(shuffle_l4_l5_)
EVE_DECLARE_CALLABLE(shuffle_l4_l5_, shuffle_l4_l5)

namespace detail
{
  EVE_ALIAS_CALLABLE(shuffle_l4_l5_, shuffle_l4_l5);
} // namespace detail

// level 2 is allowed one instruction with no mask
EVE_CALLABLE_API(shuffle_l4_l5_, shuffle_l4_l5)
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/shuffle_v2/simd/x86/shuffle_l4_l5.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/shuffle_v2/simd/arm/neon/shuffle_l4_l5.hpp>
#endif
