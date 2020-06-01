//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_CSCPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_CSCPI_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/csc.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto
  cscpi_(EVE_SUPPORTS(cpu_), restricted_type const &, T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return restricted_(csc)(a0 * Pi<T>());
    }
    else
      return apply_over(restricted_(cscpi), a0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big,  small
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cscpi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )
          return rec(a0);
        if( is_flint(a0) || is_not_finite(a0) )
          return Nan<T>(); // Nan or Inf input
      }
      T x = abs(a0);
      if constexpr( simd_value<T> )
      {
        x = if_else(is_nez(a0) && (is_not_finite(x) || is_flint(x)), eve::allbits_, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      return rec(sin_finalize(bitofsign(a0), quadrant(fn), xr, dxr));
    }
    else
      return apply_over(D()(cscpi), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cscpi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if( all(eve::abs(a0) <= T(0.25)) )
        return restricted_(cscpi)(a0);
      else
        return big_(cscpi)(a0);
    }
    else
      return apply_over(cscpi, a0);
  }
}

#endif
