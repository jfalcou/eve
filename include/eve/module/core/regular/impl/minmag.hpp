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
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
minmag_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(minmag, a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
minmag_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  auto aa = eve::abs(a);
  auto bb = eve::abs(b);
  if constexpr( simd_value<T> )
  {
    auto tmp = if_else(is_not_greater_equal(bb, aa), b, eve::min(a, b));
    return if_else(is_not_greater_equal(aa, bb), a, tmp);
  }
  else { return aa < bb ? a : bb < aa ? b : eve::min(a, b); }
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, real_value U, real_value... V>
EVE_FORCEINLINE auto
minmag_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U  t,
        V ...f) noexcept
{
  return mask_op(cond, eve::minmag, t, f...);
}


//================================================================================================
// N parameters
//================================================================================================
template<decorator D, real_value T0, real_value T1, real_value... Ts>
auto
minmag_(EVE_SUPPORTS(cpu_), D const&, T0 a0, T1 a1, Ts... args)
{
  using r_t = common_compatible_t<T0, T1, Ts...>;
  r_t that(D()(minmag)(r_t(a0), r_t(a1)));
  ((that = D()(minmag)(that, r_t(args))), ...);
  return that;
}

template<real_value T0, real_value T1, real_value... Ts>
auto
minmag_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
{
  using r_t = common_compatible_t<T0, T1, Ts...>;
  r_t that(minmag(r_t(a0), r_t(a1)));
  ((that = minmag(that, r_t(args))), ...);
  return that;
}


//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
minmag_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return minmag(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
minmag_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return d(minmag)(m...); }, tup);
}

}
