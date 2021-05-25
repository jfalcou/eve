//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/function/abs.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct rshl_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rshl_), T const&, [[ maybe_unused ]]S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(eve::abs(s)),
                  "[eve::rshl] - Shifting by " << s
                  << " is out of the range ]"
                  << -int(sizeof(value_type_t<T>) * 8)
                  << ", "
                  << sizeof(value_type_t<T>) * 8
                  << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(rshl_, rshl);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/rshl.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/rshl.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/rshl.hpp>
#endif
