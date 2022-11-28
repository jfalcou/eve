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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/numeric/maxabs.hpp>
#include <eve/module/core/pedantic/maxabs.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/abs.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> decltype(add(abs(a), abs(b)))
{
  return arithmetic_call(maxabs, a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
requires has_native_abi_v<T>
{
  return eve::max(eve::abs(a), eve::abs(b));
}

//================================================================================================
// Masked case
//================================================================================================
template<decorator D, conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_), C const& cond, D const& d, U const& t, V const& f) noexcept
-> decltype(d(maxabs)(t, f))
{
  return mask_op(cond, D()(eve::maxabs), t, f);
}

template<conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U const& t,
        V const& f) noexcept
-> decltype(maxabs(t, f))
{
  return mask_op(cond, eve::maxabs, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<decorator D, real_value T0, real_value T1, real_value... Ts>
auto
maxabs_(EVE_SUPPORTS(cpu_), D const&, T0 a0, T1 a1, Ts... args) noexcept
->  decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...))
{
  auto dma  = D()(maxabs);
  using r_t = decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...));
  r_t that(dma(r_t(a0), r_t(a1)));
  ((that = dma(that, r_t(args))), ...);
  return that;
}

template<real_value T0, real_value T1, real_value... Ts>
auto
maxabs_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) noexcept
->  decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...))
{
  using r_t = decltype(eve::add(eve::abs(a0), eve::abs(a1), eve::abs(args)...));
  r_t that(maxabs(r_t(a0), r_t(a1)));
  ((that = maxabs(that, r_t(args))), ...);
  return that;
}
//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
maxabs_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return eve::abs(get<0>(tup));
  else return kumi::apply( [&](auto... m) { return maxabs(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
maxabs_(EVE_SUPPORTS(cpu_), D const & d, Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return d(eve::abs)(get<0>(tup));
  else return kumi::apply( [&](auto... m) { return d(maxabs)(m...); }, tup);
}

// -----------------------------------------------------------------------------------------------
// N parameters Masked case
template<conditional_expr C, decorator D, value T0, value T1, value... Ts>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T0 a0, T1 a1, Ts... args) noexcept
->decltype(maxabs(a0, a1, args...))
{
  return mask_op(cond, d(eve::maxabs), a0, a1, args...);
}

template<conditional_expr C, value T0, value T1, value... Ts>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(maxabs(a0, a1, args...))
{
  return mask_op(cond, eve::maxabs, a0, a1, args...);
}
}
