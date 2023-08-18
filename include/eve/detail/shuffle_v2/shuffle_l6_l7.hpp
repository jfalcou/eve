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

// level6 and level7 combine up to 3 instructions

EVE_REGISTER_CALLABLE(shuffle_l6_l7_)
EVE_DECLARE_CALLABLE(shuffle_l6_l7_, shuffle_l6_l7)

namespace detail
{
  EVE_ALIAS_CALLABLE(shuffle_l6_l7_, shuffle_l6_l7);
} // namespace detail

// level 2 is allowed one instruction with no mask
EVE_CALLABLE_API(shuffle_l6_l7_, shuffle_l6_l7)
}

#include <eve/detail/shuffle_v2/simd/common/shuffle_l6_l7.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/shuffle_v2/simd/x86/shuffle_l6_l7.hpp>
#endif
