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
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/constant/mone.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto fsnm_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(diff_type<N>()(fsnm), a, b, c);
  }

  template<floating_value T, auto N>
  EVE_FORCEINLINE  auto fsnm_(EVE_SUPPORTS(cpu_)
                            , diff_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  //  requires(has_native_abi_v<T>)
  {
    if constexpr(N == 1) return mone(as(a));
    else if constexpr(N == 2) return minus(c);
    else if constexpr(N == 3) return minus(b);
  }

  template<auto N, conditional_expr C, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto fsnm_(EVE_SUPPORTS(cpu_)
                            , C const &cond
                            , diff_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::fsnm), a, b, c);
  }
}
