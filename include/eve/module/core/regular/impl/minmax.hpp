//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/platform.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/traits.hpp>

namespace eve::detail
{
template<typename T>
constexpr bool has_native_minmax() noexcept
{
  using e_t = element_type_t<T>;
  constexpr bool small_int = !(std::integral<e_t> && sizeof(e_t) == 8);

  if constexpr( x86_tag<current_api_type> )
  {
    return ((current_api <= avx2) && small_int) || current_api == avx512;
  }
  else if constexpr( arm_tag<current_api_type> )
  {
    if constexpr( current_api >= asimd ) return small_int; else return sizeof(e_t) != 8;
  }
  else return true;
};

// -----  Regular
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
EVE_FORCEINLINE auto
minmax_(EVE_SUPPORTS(cpu_), T0 v0, T1 v1, Ts... vs) noexcept
    -> decltype(kumi::tuple {eve::min(v0, v1, vs...), eve::max(v0, v1, vs...)})
{
  if constexpr( has_native_minmax<common_value_t<T0,T1,Ts...>>() )
  {
    return kumi::tuple {eve::min(v0, v1, vs...), eve::max(v0, v1, vs...)};
  }
  else
  {
    // If there is no native min/max, we compute the check once
    // We use > cause it is more often optimized than <
    auto check = v0 > v1;
    return kumi::tuple {if_else(check, v1, v0), if_else(check, v0, v1)};
  }
}

// -----  Masked case
template<conditional_expr C, ordered_value T0, ordered_value T1, ordered_value... Ts>
EVE_FORCEINLINE auto
minmax_(EVE_SUPPORTS(cpu_), C const& c, T0 v0, T1 v1, Ts... vs) noexcept
    -> decltype(kumi::tuple {eve::min[c](v0, v1, vs...), eve::max[c](v0, v1, vs...)})
{
  return kumi::tuple {eve::min[c](v0, v1, vs...), eve::max[c](v0, v1, vs...)};
}

// -----  Tuple case
template<kumi::non_empty_product_type Ts>
EVE_FORCEINLINE auto
minmax_(EVE_SUPPORTS(cpu_), Ts tup) noexcept -> decltype(kumi::tuple {eve::min(tup), eve::max(tup)})
{
  return kumi::apply([&](auto... m) { return minmax(m...); }, tup);
}

// -----  Predicate case
template<typename Callable>
EVE_FORCEINLINE auto
minmax_(EVE_SUPPORTS(cpu_), Callable f)
{
  if constexpr( std::same_as<Callable, callable_is_less_> ) return eve::minmax;
  else if constexpr( std::same_as<Callable, callable_is_greater_> )
  {
    return [](auto x, auto y) { return kumi::tuple {max(x, y), min(x, y)}; };
  }
  else
  {
    return [f](auto x, auto y)
    {
      auto check = f(y, x);
      return kumi::tuple {if_else(check, y, x), if_else(check, x, y)};
    };
  }
}
}
