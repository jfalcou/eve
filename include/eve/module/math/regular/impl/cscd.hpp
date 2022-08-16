//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/regular/sind.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr auto
cscd_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( std::is_same_v<D, quarter_circle_type> ) { return rec(D()(sind)(a0)); }
    else
    {
      auto a0_180 = div_180(a0);
      auto test   = is_nez(a0_180) && is_flint(a0_180);
      if constexpr( scalar_value<T> ) // early return for nans in scalar case
      {
        if( test ) return nan(eve::as<T>());
      }
      return if_else(test, eve::allbits, rec(D()(sind)(a0)));
    }
  }
  else return apply_over(D()(cscd), a0);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cscd_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  return cscd(regular_type(), a0);
}


// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
cscd_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::cscd, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
cscd_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::cscd), t);
}
}
