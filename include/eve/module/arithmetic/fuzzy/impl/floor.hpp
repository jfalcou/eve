//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/arithmetic/constant/eps.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/fuzzy.hpp>
#include <eve/function/trunc.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/prev.hpp>

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
