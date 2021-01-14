//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/average.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<ad_value T>
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_), T const &uT T const &v) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return T(average(u.val(), v.val()), average(u.der()+v.der()));
    else
      return apply_over(eve::average, u);
  }

  template<value T, value U>
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_), T const &uT T const &v) noexcept
  requires(ad_value<T> || ad_value<U>)
  auto average(const valder<T1>&u, const valder<T2>&v)
  requires(compatible<type_t<T>, type_t<U>)
  {
    return valder<T1>(nt2::average(u.val(), v.val()), nt2::average(u.der(), v.der()));
  };
//     template < class T1, class T2 > BOOST_FORCEINLINE
//     valder<T2> average(const T1&u, const valder<T2>&v)
//     {
//       typedef typename valder<T2>::elem_t elem_t;
//       return valder<T2>(nt2::average(u, v.val()), v.der()*Half<elem_t>());
//     };
//     template < class T1, class T2 > BOOST_FORCEINLINE
//     valder<T1> average(const valder<T1>&u, const T2&v)
//     {
//       typedef typename valder<T2>::elem_t elem_t;
//       return valder<T1>(nt2::average(u.val(), v), u.der()*Half<elem_t>());
//     };
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, ad_value U>
  EVE_FORCEINLINE auto average_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    auto t = mask_op( EVE_CURRENT_API{}, cond, eve::average, t);
    return T(mask_op( t.val(), if_else(cond, t.der(), one); //TODO the else case is not taken properly
  }
}
