//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/constant/mone.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto fms_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(diff_type<N>()(fms), a, b, c);
  }

  template<floating_value T, auto N>
  EVE_FORCEINLINE  auto fms_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr(N == 1) return b;
    else if constexpr(N == 2) return a;
    else if constexpr(N == 3) return mone(as(c));
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  // -----------------------------------------------------------------------------------------------
  template<auto N, conditional_expr C, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto fms_(EVE_SUPPORTS(cpu_)
                            , C const &cond
                            , diff_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires properly_convertible<U, V, T>
  {
    using r_t =  common_compatible_t<T, U, V>;
    return mask_op(  cond, diff_nth<N>(eve::fms), r_t(a), r_t(b), r_t(c));
  }

}
