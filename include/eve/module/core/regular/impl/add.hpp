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
#include <eve/traits/common_compatible.hpp>
#include <type_traits>

namespace eve::detail
{
//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, value U, value... Vs>
EVE_FORCEINLINE auto
add_(EVE_SUPPORTS(cpu_),
     C const& cond,
     U    t,
     Vs... fs) noexcept
{
  return mask_op(cond, eve::add, t, fs...);
}

//================================================================================================
// N parameters
//================================================================================================
template<decorator D, value T0, value... Ts>
 common_compatible_t<T0, Ts...>
add_(EVE_SUPPORTS(cpu_), D const& d, T0 a0, Ts... args) requires(compatible_values<T0, Ts>&&...)
{
  common_compatible_t<T0, Ts...> that(a0);
  ((that = d(add)(that, args)), ...);
  return that;
}

template<value T0, value... Ts>
auto
add_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args) requires(compatible_values<T0, Ts>&&...)
{
  common_compatible_t<T0, Ts...> that(a0);
  ((that = add(that, args)), ...);
  return that;
}

//================================================================================================
// product type
//================================================================================================
template<value T0, value ... Ts>
auto
add_(EVE_SUPPORTS(cpu_), T0 a0, kumi::tuple<Ts...> args)
{
  constexpr auto I = kumi::locate(args, kumi::predicate<eve::is_simd_value>());
  if constexpr(I < kumi::size_v<decltype(args)>)
  {
    common_compatible_t<T0, decltype(get<I>(args))> that(a0);
    return kumi::fold_left(eve::add, args, that);
  }
  else
  {
    T0 that(a0);
    return kumi::fold_left(eve::add, args, that);
  }
}

template<kumi::product_type Ts>
auto
add_(EVE_SUPPORTS(cpu_), Ts args)
{
  if constexpr( kumi::size_v<Ts> == 0) return 0;
  else if constexpr( kumi::size_v<Ts> == 1) return get<0>(args);
  else
  {
    return add(get<0>(args), kumi::pop_front(args));
  }
}

}
