//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/iceil.hpp>
#include <eve/function/ifloor.hpp>
#include <eve/function/inearest.hpp>
#include <eve/function/itrunc.hpp>

namespace eve::detail
{

  template<real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto iround_(EVE_SUPPORTS(cpu_), D const &, T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( std::is_same_v<D, eve::upward_type> )
        return eve::iceil(a);
      else if constexpr( std::is_same_v<D, eve::downward_type> )
        return eve::ifloor(a);
      else if constexpr( std::is_same_v<D, eve::toward_zero_type> )
        return eve::itrunc(a);
      else if constexpr( std::is_same_v<D, eve::to_nearest_type> )
        return eve::inearest(a);
    }
    else
      return apply_over(D()(iround), a);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr auto iround_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return eve::inearest(a);
  }

}
