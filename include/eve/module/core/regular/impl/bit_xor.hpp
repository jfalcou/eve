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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
bit_xor_(EVE_SUPPORTS(cpu_),
         C const& cond,
         U const& t,
         V const& f) noexcept requires bit_compatible_values<U, V>
{
  return mask_op(cond, eve::bit_xor, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
auto
bit_xor_(EVE_SUPPORTS(cpu_),
         T0 a0,
         T1 a1,
         Ts... args) requires bit_compatible_values<T0, T1> &&(bit_compatible_values<T1, Ts>&&...)
{
  auto that = bit_xor(a0, a1);
  ((that = bit_xor(that, args)), ...);
  return that;
}

template<conditional_expr C, real_value T0, real_value T1, real_value... Ts>
auto
bit_xor_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) requires
    bit_compatible_values<T0, T1> &&(bit_compatible_values<T1, Ts>&&...)
{
  auto that = bit_xor(a1, args...);
  return mask_op(cond, eve::bit_xor, a0, that);
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
bit_xor_(EVE_SUPPORTS(cpu_), Ts const & args)
{
  if constexpr(kumi::size_v<Ts> == 1) return get<0>(args);
  else if constexpr(kumi::size_v<Ts> == 2) return bit_xor(get<0>(args), get<1>(args));
  else return kumi::apply(bit_xor, args);
}

template<conditional_expr C, kumi::non_empty_product_type Ts>
auto
bit_xor_(EVE_SUPPORTS(cpu_), C const& cond, Ts const & args)
{
  if constexpr(kumi::size_v<Ts> == 1) return get<0>(args);
  else return kumi::apply( [&](auto... m) { return mask_op(cond, eve::bit_xor, m...); }, args);
}

}
