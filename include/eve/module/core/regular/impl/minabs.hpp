//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/min.hpp>

#include <type_traits>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> decltype(add(abs(a), abs(b)))
{
  return arithmetic_call(minabs, a, b);
}

template<value T>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
requires has_native_abi_v<T>
{
  return eve::min(eve::abs(a), eve::abs(b));
}

//================================================================================================
// Masked case
//================================================================================================
template<decorator D, conditional_expr C, value U, value V>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_), C const& cond, D const&, U const& t, V const& f) noexcept
requires(std::convertible_to<U, decltype(minabs(t, f))>)
{
  return mask_op(cond, D()(eve::minabs), t, f);
}

template<conditional_expr C, value U, value V>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U const& t,
        V const& f) noexcept
requires(std::convertible_to<U, decltype(minabs(t, f))>)
{
  return mask_op(cond, eve::minabs, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<decorator D, value T0, value T1, value... Ts>
auto
minabs_(EVE_SUPPORTS(cpu_), D const&, T0 a0, T1 a1, Ts... args) noexcept
->  decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...))
{
  auto dma  = D()(min);
  using r_t = decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...));
  r_t that(dma(eve::abs(a0), eve::abs((a1))));
  ((that = dma(that, eve::abs(args))), ...);
  return that;
}

template<value T0, value T1, value... Ts>
auto
minabs_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) noexcept
->  decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...))
{
  using r_t = decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...));
  r_t that(min(eve::abs(a0), eve::abs((a1))));
  ((that = min(that, eve::abs(args))), ...);
  return that;
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
minabs_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return eve::abs(get<0>(tup));
  else return kumi::apply( [&](auto... m) { return minabs(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
minabs_(EVE_SUPPORTS(cpu_), D const & d, Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return d(eve::abs)(get<0>(tup));
  else return kumi::apply( [&](auto... m) { return d(minabs)(m...); }, tup);
}

// -----------------------------------------------------------------------------------------------
// N parameters Masked case
template<conditional_expr C, decorator D, value T0, value T1, value... Ts>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T0 a0, T1 a1, Ts... args) noexcept
requires(std::convertible_to<T0, decltype(minabs(a0, a1, args...))>)
{
  return mask_op(cond, d(eve::minabs), a0, a1, args...);
}

template<conditional_expr C, value T0, value T1, value... Ts>
EVE_FORCEINLINE auto
minabs_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) noexcept
requires(std::convertible_to<T0, decltype(minabs(a0, a1, args...))>)
{
  return mask_op(cond, eve::minabs, a0, a1, args...);
}
}
