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
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/average.hpp>
#include <eve/module/core/regular/exponent.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/regular/sqrt.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{

  template<value T, value U>
  EVE_FORCEINLINE auto agm_(EVE_SUPPORTS(cpu_)
                           , T aa,  U bb) noexcept
  requires (std::is_floating_point_v<eve::underlying_type_t<common_value_t<T, U>>>)
  {
    using v_t = common_value_t<T, U>;
    if constexpr(has_native_abi_v<v_t>)
    {
      v_t a(aa);
      v_t b(bb);
      auto ex = exponent(average(a, b));
      auto r     = nan(as(average(a, b)));
      auto null = is_eqz(a)||is_eqz(b);
      r = if_else(null, zero, r);
      auto infi = is_infinite(a) || is_infinite(b);
      r = if_else(infi, a+b, r);
      auto unord = is_unordered(a, b);
      auto done = is_lez(sign(a)*sign(b)) || unord || infi;
      a = if_else(done,  zero, a);
      b = if_else(done,  zero, b);
      a =  ldexp(a, -ex);
      b =  ldexp(b, -ex);
      auto c  = average(a, -b);
      while (eve::any(eve::abs(c) > v_t(2)*eps(as(c))))
      {
        auto an=average(a, b);
        auto bn=sqrt(a*b);
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return if_else(done, r, ldexp(b, ex));
    }
    else
      return apply_over(agm, aa, bb);
  }


  template<conditional_expr C, value T, value U>
  auto
  agm_(EVE_SUPPORTS(cpu_),
       C const& cond,
       T        a0,
       U        a1) noexcept
  -> common_value_t<T, U>
  {
    return mask_op(cond, eve::agm, a0, a1);
  }
}
