//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
  template<unsigned_value T>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(cpu_)
                                , T const &v) noexcept
  {
    using r_t = as_integer_t<T, unsigned>;
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        return r_t(std::popcount(v));
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

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, unsigned_value  U>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, eve::popcount, t);
  }
}
