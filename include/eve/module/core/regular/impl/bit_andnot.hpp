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
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
bit_andnot_(EVE_SUPPORTS(cpu_),
            T const& a,
            U const& b) noexcept requires bit_compatible_values<T, U>
{
  return bit_call(bit_andnot, a, b);
}

template<scalar_value T>
EVE_FORCEINLINE auto
bit_andnot_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr( floating_value<T> )
  {
    using b_t = as_integer_t<T, unsigned>;
    return bit_cast(b_t(bit_cast(a, as<b_t>()) & ~bit_cast(b, as<b_t>())), as(a));
  }
  else return T(a & ~b);
}

template<simd_value T>
EVE_FORCEINLINE T
bit_andnot_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  return apply_over(bit_andnot, a, b); // fallback never taken if proper intrinsics are at hand
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value U, value V>
EVE_FORCEINLINE auto
bit_andnot_(EVE_SUPPORTS(cpu_),
            C const& cond,
            U const& t,
            V const& f) noexcept requires bit_compatible_values<U, V>
{
  return mask_op(cond, eve::bit_andnot, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<value T0, value T1, value... Ts>
auto
bit_andnot_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) requires
    bit_compatible_values<T0, T1> &&(bit_compatible_values<T1, Ts>&&...)
{
  auto that = bit_or(a1, args...);
  return bit_andnot(a0, that);
}

template<conditional_expr C, value T0, value T1, value... Ts>
auto
bit_andnot_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) requires
    bit_compatible_values<T0, T1> &&(bit_compatible_values<T1, Ts>&&...)
{
  auto that = bit_or(a1, args...);
  return mask_op(cond, eve::bit_andnot, a0, that);
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
bit_andnot_(EVE_SUPPORTS(cpu_), Ts const & args)
{
  if constexpr(kumi::size_v<Ts> == 1) return get<0>(args);
  else if constexpr(kumi::size_v<Ts> == 2) return bit_andnot(get<0>(args), get<1>(args));
  else return bit_andnot(get<0>(args), kumi::apply(bit_or, kumi::pop_front(args)));
}

template<conditional_expr C, kumi::non_empty_product_type Ts>
auto
bit_andnot_(EVE_SUPPORTS(cpu_), C const& cond, Ts const & args)
{
  if constexpr(kumi::size_v<Ts> == 1) return get<0>(args);
  else return kumi::apply( [&](auto... m) { return mask_op(cond, eve::bit_andnot, m...); }, args);
}

}
