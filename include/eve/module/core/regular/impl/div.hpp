//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/detail/multi_mul.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_andnot.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/module/core/regular/trunc.hpp>

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4723) // potential divide by 0
#endif

#include <eve/module/core/regular/impl/div_downward.hpp>
#include <eve/module/core/regular/impl/div_tonearest.hpp>
#include <eve/module/core/regular/impl/div_upward.hpp>

namespace eve::detail
{
template<value T, value U, decorator D>
EVE_FORCEINLINE auto
div_(EVE_SUPPORTS(cpu_), D const&, T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(D()(div), a, b);
}

//////////////////////////////////////////////////////////////////////
//== toward_zero
template<value T>
EVE_FORCEINLINE auto
div_(EVE_SUPPORTS(cpu_), toward_zero_type const&, T const& a, T const& b) noexcept
{
  EVE_ASSERT(eve::all(is_nez(b)), "[eve] - div(0, 0) is undefined");
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( floating_value<T> ) { return trunc(div(a, b)); }
    else { return div(a, b); }
  }
  else return apply_over(toward_zero(div), a, b);
}

//================================================================================================
//== Masked case
//================================================================================================
template<conditional_expr C, value U, value V>
EVE_FORCEINLINE auto
div_(EVE_SUPPORTS(cpu_), C const& cond, U t, V f) noexcept requires compatible_values<U, V>
{
  auto g = if_else(cond, f, one);
  return if_else(cond, eve::div(t, g), t);
}

template<conditional_expr C, decorator D, value U, value V>
EVE_FORCEINLINE auto
div_(EVE_SUPPORTS(cpu_), C const& cond, D const&, U const& t, V const& f) noexcept requires
    compatible_values<U, V>
{
  auto g = if_else(cond, f, one);
  return if_else(cond, D()(div)(t, g), t);
}

//================================================================================================
//==  regular N parameters
//================================================================================================
template<value T0, value T1, value... Ts>
auto
div_(EVE_SUPPORTS(cpu_),
     T0 a0,
     T1 a1,
     Ts... args) requires compatible_values<T0, T1> &&(compatible_values<T0, Ts>&&...)
{
  using r_t = common_compatible_t<T0, T1, Ts...>;
  r_t that(a1);
  that = mul(that, r_t(args)...);
  EVE_ASSERT(eve::all(is_nez(that)), "[eve] div - 0/0 is undefined");
  return div(r_t(a0), that);
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
div_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return div(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
div_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return d(div)(m...); }, tup);
}

}

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(pop)
#endif
