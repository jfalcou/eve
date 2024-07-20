//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/mzero.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
  template<value T, callable_options O>
  constexpr T  abs_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
  {
    if constexpr(O::contains(saturated2))
    {
      if      constexpr( signed_integral_scalar_value<T>  ) return  ( (v == valmin(eve::as(v)))
                                                                    ? valmax(eve::as(v)) : eve::abs(v)
                                                                    );
      else if constexpr( signed_integral_simd_value<T>    ) return if_else( v == valmin(eve::as(v))
                                                                          , valmax(eve::as(v)), eve::abs(v)
                                                                          );
      else                                                  return eve::abs(v);
    }
    else
    {
      if      constexpr( floating_value<T> )                return bit_andnot(v, mzero(eve::as(v)));
      else if constexpr( unsigned_value<T> )                return v;
      else if constexpr( signed_integral_scalar_value<T> )  return v < T(0) ? -v : v;
      else                                                  return eve::max(v, -v);
    }
  }
}
