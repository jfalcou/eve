//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/rec.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<value T, value U>
EVE_FORCEINLINE auto
average_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(average, a, b);
}

template<value T>
EVE_FORCEINLINE T
average_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  if constexpr( integral_value<T> ) return (a & b) + ((a ^ b) >> 1);
  else return fma(a, half(eve::as(a)), b * half(eve::as(a)));
}

// -----------------------------------------------------------------------------------------------
// raw case
template<value T, value U>
EVE_FORCEINLINE auto
average_(EVE_SUPPORTS(cpu_),
         raw_type const&,
         T const& a,
         U const& b) noexcept requires compatible_values<T, U>
{
  return average(a, b);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
average_(EVE_SUPPORTS(cpu_),
         C const& cond,
         U const& t,
         V const& f) noexcept requires compatible_values<U, V>
{
  return mask_op(cond, eve::average, t, f);
}

//================================================================================================
// N parameters
//================================================================================================

template<value T0, value... Ts>
auto
average_(EVE_SUPPORTS(cpu_),
         T0 a0,
         Ts... args) requires floating_value<common_compatible_t<T0, Ts...>>
{
  using r_t   = common_compatible_t<T0, Ts...>;
  using elt_t = element_type_t<r_t>;
  elt_t invn  = rec(elt_t(sizeof...(args) + 1u));
  r_t   that(a0 * invn);
  auto  next = [invn](auto avg, auto x) { return fma(x, invn, avg); };
  ((that = next(that, args)), ...);
  return that;
}

template<value T0, value... Ts>
auto
average_(EVE_SUPPORTS(cpu_),
         raw_type const&,
         T0 a0,
         Ts... args) requires floating_value<common_compatible_t<T0, Ts...>>
{
  common_compatible_t<T0, Ts...> that(a0);
  ((that = add(that, args)), ...);
  return that / (sizeof...(args) + 1);
}

template<conditional_expr C, value T0, value... Ts>
auto
average_(EVE_SUPPORTS(cpu_),
         C const& cond,
         T0       a0,
         Ts... args) requires floating_value<common_compatible_t<T0, Ts...>>
{
  return mask_op(cond, eve::average, a0, args...);
}

}
