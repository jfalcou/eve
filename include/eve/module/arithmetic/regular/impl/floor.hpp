//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/arithmetic/regular/dec.hpp>
#include <eve/module/arithmetic/regular/is_greater.hpp>
#include <eve/module/arithmetic/regular/trunc.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
                                    , T const &a0) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      T z = eve::trunc(a0);
      return dec[ z > a0 ](z);
    }
    else return apply_over(floor, a0);
  }


  ////////////////////////////////////////////////////////////////////////////////////
  // return integral types

  template<integral_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto floor_(EVE_SUPPORTS(cpu_), D const &, T xx) noexcept
  requires(is_one_of<D>(types<int_converter, uint_converter>{}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      return D()(floor(xx));
    }
    else
    {
      return apply_over(D()(floor), xx);
    }
  }
}
