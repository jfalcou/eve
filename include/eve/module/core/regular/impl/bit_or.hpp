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
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_ornot.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
bit_or_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U const& t,
        V const& f) noexcept requires bit_compatible_values<U, V>
{
  return mask_op(cond, eve::bit_or, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
bit_or_(EVE_SUPPORTS(cpu_),
        T0 a0,
        T1 a1,
        Ts... args) requires bit_compatible_values<T0, T1> &&(bit_compatible_values<T1, Ts>&&...)
{
  auto that = bit_or(a0, a1);
  ((that = bit_or(that, args)), ...);
  return that;
}

template<conditional_expr C, ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
bit_or_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) requires
    bit_compatible_values<T0, T1> &&(bit_compatible_values<T1, Ts>&&...)
{
  auto that = bit_or(a1, args...);
  return mask_op(cond, eve::bit_or, a0, that);
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
bit_or_(EVE_SUPPORTS(cpu_), Ts const & args)
{
  if constexpr(kumi::size_v<Ts> == 1) return get<0>(args);
  else if constexpr(kumi::size_v<Ts> == 2) return bit_or(get<0>(args), get<1>(args));
  else return kumi::apply(bit_or, args);
}

template<conditional_expr C, kumi::non_empty_product_type Ts>
auto
bit_or_(EVE_SUPPORTS(cpu_), C const& cond, Ts const & args)
{
  if constexpr(kumi::size_v<Ts> == 1) return get<0>(args);
  else return kumi::apply( [&](auto... m) { return mask_op(cond, eve::bit_or, m...); }, args);
}

}
