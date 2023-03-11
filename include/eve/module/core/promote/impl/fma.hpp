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
#include <eve/detail/skeleton_calls.hpp>

#include <type_traits>

namespace eve::detail
{
  template<ordered_value T, ordered_value U, ordered_value V>
  EVE_FORCEINLINE auto
  fma_(EVE_SUPPORTS(cpu_), promote_type const&, T const& a, U const& b, V const& c) noexcept
  {
   using et_t =  element_type_t<T>;
   using eu_t =  element_type_t<U>;
   using ev_t =  element_type_t<V>;
   using er_t = common_type_t<et_t, eu_t, ev_t>;
   constexpr int ct = cardinal_v<T>;
   constexpr int cu = cardinal_v<U>;
   constexpr int cv = cardinal_v<V>;
   constexpr int Ntu = ct < cu ? cu : cv;
   constexpr int N   = cv < Ntu ? Ntu : cv;
   using r_t = wide<er_t, fixed<N>>;
   auto cv_t = as(eve::as<er_t>());
   if constexpr(has_native_abi_v<r_t>)
   {
     return fma(convert(a, cv_t), convert(b, cv_t), convert(c,cv_t));
   }
   else
     return apply_over(fma, convert(a, cv_t), convert(b, cv_t), convert(c, cv_t));
  }

}
