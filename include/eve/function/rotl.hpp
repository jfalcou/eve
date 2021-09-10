//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/abs.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct rotl_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(regular_type, eve::tag::rotl_), T const& , [[ maybe_unused ]] S const& s)
    {
      constexpr int l [[ maybe_unused ]] = sizeof(value_type_t<T>) * 8;
      EVE_ASSERT( assert_good_shift<T>(eve::abs(s)),
                  "[eve::rotl] Rotating by " << s
                                             << " is out of the range ]"
                                             << -l
                                             << ", "
                                             << l
                                             << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(rotl_, rotl);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/rotl.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/rotl.hpp>
#endif
