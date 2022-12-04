//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/binarize.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// Decorated
template<ordered_value T>
EVE_FORCEINLINE constexpr T
oneminus_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& v) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    using elt_t = element_type_t<T>;
    if constexpr( std::is_floating_point_v<elt_t> ) { return one(eve::as<T>()) - v; }
    else
    {
      if constexpr( std::is_unsigned_v<elt_t> ) { return binarize(is_eqz(v)); }
      if constexpr( scalar_value<T> )
      {
        return (v <= valmin(eve::as(v)) + 2) ? valmax(eve::as(v)) : oneminus(v);
      }
      else if constexpr( simd_value<T> )
      {
        return if_else(v < valmin(eve::as(v)) + 2, valmax(eve::as(v)), oneminus(v));
      }
    }
  }
  else { return apply_over(saturated(oneminus), v); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value U>
EVE_FORCEINLINE auto
oneminus_(EVE_SUPPORTS(cpu_), C const& cond, saturated_type const&, U const& t) noexcept
{
  return mask_op(cond, saturated(eve::oneminus), t);
}
}
