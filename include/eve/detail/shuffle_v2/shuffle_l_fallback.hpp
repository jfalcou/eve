//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/shuffle_v2_fwd.hpp>

namespace eve
{
EVE_REGISTER_CALLABLE(shuffle_l_fallback_)
EVE_DECLARE_CALLABLE(shuffle_l_fallback_, shuffle_l_fallback)

namespace detail
{
  EVE_ALIAS_CALLABLE(shuffle_l_fallback_, shuffle_l_fallback);
} // namespace detail

// l fallback does some of known things that are quite bad
// but are the best we can do in some cases.
EVE_CALLABLE_API(shuffle_l_fallback_, shuffle_l_fallback)
}

#include <eve/detail/shuffle_v2/simd/common/shuffle_l_fallback.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/shuffle_v2/simd/x86/shuffle_l_fallback.hpp>
#endif
