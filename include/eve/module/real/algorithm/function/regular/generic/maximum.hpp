//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/max.hpp>

namespace eve::detail
{
  template<real_value T> EVE_FORCEINLINE auto maximum_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return v;
    }
    else if constexpr( simd_value<T> )
    {
      using elt_t =  element_type_t<T>;
      elt_t r = v.get(0);
      for(size_t i=1; i < T::static_size ; ++i)
      {
        r = max(r, v.get(i));
      }
      return r;
    }
  }
}
