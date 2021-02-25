//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>
#include <eve/as.hpp>
#include <eve/traits.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <bit>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{
  template<integral_value T>
  EVE_FORCEINLINE as_integer_t<T, unsigned> popcount_(EVE_SUPPORTS(cpu_)
                                                     , T const &v) noexcept
  {
    using r_t = as_integer_t<T, unsigned>;
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        return r_t(std::popcount(bit_cast(v, as<r_t>())));
      }
      else
      {
        return map(eve::popcount, v);
      }
    }
    else
    {
      return apply_over(popcount, v);
    }
  }
}
