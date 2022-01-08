//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/saturated/convert.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_), downward_type const &, T a, T b) noexcept
      requires has_native_abi_v<T>
  {
    if constexpr(integral_value<T> )
    {
      EVE_ASSERT(eve::all((b!= 0)), "[eve] - downward(div)(a, 0) is undefined");
    }
    using elt_t = element_type_t<T>;
    if constexpr( floating_real_value<T> )
    {
      return floor(div(a, b));
    }
    else if constexpr( integral_real_value<T> )
    {
      if constexpr( signed_value<T> )
      {
        if constexpr( std::is_same_v<elt_t, std::int64_t> )
        {
          auto q =  div(a, b);
          auto r = fms(q, b, a);
          auto test = if_else(is_ltz(b), is_ltz(r), is_gtz(r));
          return dec[test](q);
        }
        else
        {
          return saturated(convert)(floor(float64(a) / float64(b)), as<elt_t>());
        }
      }
      else if constexpr( unsigned_value<T> )
      {
        return div(a, b);
      }
    }
  }
}
