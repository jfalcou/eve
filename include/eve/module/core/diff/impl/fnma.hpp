//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto fnma_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(diff_type<N>{}(fnma), a, b, c);
  }

  template<floating_value T, auto N>
  EVE_FORCEINLINE  auto fnma_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr(N == 1) return minus(b);
    else if constexpr(N == 2) return minus(a);
    else if constexpr(N == 3) return one(as(c));
  }

//   //================================================================================================
//   // Masked case
//   //================================================================================================
//   template<auto N, conditional_expr C, real_value T, real_value U, real_value V>
//   EVE_FORCEINLINE auto fnma(EVE_SUPPORTS(cpu_)
//                            , C const &cond
//                            , diff_type<N> const &
//                            , T const &a
//                            , U const &b
//                            , V const &c) noexcept
//   // requires properly_convertible<U, V, T>
//   {
//     return mask_op(  cond, eve::diff_nth<N>(eve::fnma), a, b, c);
//  //    using r_t =  common_compatible_t<T, U, V>;
//  //   return mask_op(  cond, diff_nth<N>(eve::fnma), r_t(a), r_t(b), r_t(c));
//   }
}
