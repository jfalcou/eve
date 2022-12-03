//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/rem.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
rem_(EVE_SUPPORTS(cpu_),
     pedantic_type const&,
     T const& a,
     U const& b) noexcept
-> decltype(rem(a, b))
{
  return arithmetic_call(pedantic(rem), a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
rem_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a, T const& b) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto bb = if_else(is_nez(b), b, one);
    if constexpr( floating_value<T> )
    {
      return if_else(is_eqz(b) || is_infinite(a) || is_unordered(a, b),
                     allbits,
                     if_else(is_eqz(a) || is_infinite(b),
                             a,
                             pedantic(fnma)(b, trunc(div(a, b)), a) // rem(a, b)
                             ));                                    // as remainder
    }
    else return if_else(is_nez(b), rem(a, bb), a);
  }
  else return apply_over(pedantic(rem), a, b);
}

template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
rem_(EVE_SUPPORTS(cpu_),
     C const& cond,
     pedantic_type const&,
     U const& t,
     V const& f) noexcept
-> decltype(rem(t, f))
{
  auto g = if_else(cond, f, one);
  return mask_op(cond, pedantic(rem), t, g);
}
}
