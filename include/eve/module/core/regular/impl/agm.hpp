//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/average.hpp>
#include <eve/module/core/regular/exponent.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/regular/sqrt.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
//   template<value T, value U>
//   EVE_FORCEINLINE  auto agm_(EVE_SUPPORTS(cpu_)
//                             , T const &a
//                             , U const &b) noexcept
//   requires compatible_values<T, U>
//   {
//     return arithmetic_call(agm, a, b);
//   }

  template<value T, value U>
  EVE_FORCEINLINE auto agm_(EVE_SUPPORTS(cpu_)
                             , T aa,  U bb) noexcept
  {
    using r_t = decltype(eve::add(aa, bb));
    r_t a(aa);
    r_t b(bb);
    if constexpr(has_native_abi_v<r_t>)
    {
      auto ex = exponent(average(a, b));
      auto r = nan(as(a));
      auto null = is_eqz(a)||is_eqz(b);
      r = if_else(null, zero, r);
      auto infi = is_infinite(a) || is_infinite(b);
      r = if_else(infi, add(a, b), r);
      auto unord = is_unordered(a, b);
      auto done = is_lez(sign(a)*sign(b)) || unord || infi;
      a = if_else(done,  zero, a);
      b = if_else(done,  zero, b);
      a =  ldexp(a, -ex);
      b =  ldexp(b, -ex);
      auto c = one(as(a)); //mul(200, eps(as(a)));
      while (eve::any(eve::abs(c) > eps(as(a))))
      {
        auto an=average(a, b);
        auto bn=sqrt(mul(a, b));
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return if_else(done, r, ldexp(b, ex));
    }
    else
      return apply_over(agm, a, b);
  }

  template<conditional_expr C, floating_real_value T, floating_real_value U>
  auto agm_(EVE_SUPPORTS(cpu_), C const &cond, T a0, U a1)
  requires floating_value<common_compatible_t<T, U>>
  {
   return mask_op(  cond, eve::agm, a0, a1);
  }


}
