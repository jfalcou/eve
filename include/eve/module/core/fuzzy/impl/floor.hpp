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
#include <eve/module/arithmetic/constant/eps.hpp>
#include <eve/module/arithmetic/regular/copysign.hpp>
#include <eve/module/arithmetic/regular/dec.hpp>
#include <eve/module/arithmetic/regular/inc.hpp>
#include <eve/module/arithmetic/regular/is_greater.hpp>
#include <eve/module/arithmetic/regular/is_lez.hpp>
#include <eve/module/arithmetic/regular/is_ltz.hpp>
#include <eve/module/arithmetic/regular/max.hpp>
#include <eve/module/arithmetic/regular/min.hpp>
#include <eve/module/arithmetic/regular/oneminus.hpp>
#include <eve/module/arithmetic/regular/trunc.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/module/arithmetic/regular/prev.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0
                                    , U const &n) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(tolerant(floor), a0, n);
  }

  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0
                                    , [[maybe_unused]] U const &n) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      return floor(next(a0, n));
    }
    else return apply_over(tolerant(floor), a0, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0
                                    , T const &ct) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      // Hagerty's FL5 function
      auto q = if_else(is_ltz(a0), one, oneminus(ct));
      auto rmax = q/(T(2)-ct);
      auto eps5 = ct/q;
      auto r = floor(a0+eve::max(ct, min(rmax, eps5*eve::abs(inc(floor(a0))))));
      return if_else(is_lez(a0) || (r-a0 < rmax), r, dec(r));
    }
    else return apply_over(tolerant(floor), a0, ct);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0) noexcept
  {
    return tolerant_type()(floor)(a0,  3*eps(as(a0)));
  }


  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto floor_(EVE_SUPPORTS(cpu_), C const &cond, tolerant_type const &, U const &t) noexcept
  {
    return mask_op(  cond, tolerant(eve::floor), t);
  }

}
