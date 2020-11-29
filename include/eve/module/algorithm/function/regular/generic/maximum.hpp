//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
      elt_t r = v[0];
      for(size_t i=1; i < T::static_size ; ++i)
      {
        r = max(r, v[i]);
      }
      return r;
    }
  }
}
