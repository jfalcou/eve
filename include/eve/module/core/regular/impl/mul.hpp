//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/multi_mul.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
//================================================================================================
//== Masked case
//================================================================================================
template<conditional_expr C, value U, value... V>
EVE_FORCEINLINE auto
mul_(EVE_SUPPORTS(cpu_),
     C const& cond,
     U    t,
     V... f) noexcept
{
  return mask_op(cond, eve::mul, t, f...);
}

//================================================================================================
//==  regular N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
common_compatible_t<T0, T1, Ts...>
mul_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
{
  using r_t = common_compatible_t<T0, T1, Ts...>;
  r_t that(mul(r_t(a0), r_t(a1)));
  ((that = mul(that, r_t(args))), ...);
  return that;
}

//================================================================================================
// product type
//================================================================================================
template<value T0, value ... Ts>
auto
mul_(EVE_SUPPORTS(cpu_), T0 a0, kumi::tuple<Ts...> args)
{
  constexpr auto I = kumi::locate(args, kumi::predicate<eve::is_simd_value>());
  if constexpr(I < kumi::size_v<decltype(args)>)
  {
    common_compatible_t<T0, decltype(get<I>(args))> that(a0);
    return kumi::fold_left(eve::mul, args, that);
  }
  else
  {
    T0 that(a0);
    return kumi::fold_left(eve::mul, args, that);
  }
}

template<kumi::product_type Ts>
auto
mul_(EVE_SUPPORTS(cpu_), Ts args)
{
  if constexpr( kumi::size_v<Ts> == 0) return 1;
  else if constexpr( kumi::size_v<Ts> == 1) return get<0>(args);
  else
  {
    return mul(get<0>(args), kumi::pop_front(args));
  }
}

}
