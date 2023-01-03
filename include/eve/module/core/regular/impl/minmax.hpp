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
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/traits.hpp>

namespace eve::detail
{
template<typename W>
constexpr bool prefer_min_max() noexcept
{
  if constexpr( scalar_value<W> ) return true;
  else
  {
    using enum category;
    constexpr bool is_ints64 = match(categorize<W>(), int64x4, uint64x4, int64x2, uint64x2);

    // AVX is fine for non-64 bits as its min/max on other types has been fixed
    if constexpr( x86_tag<current_api_type> )       return current_api == avx512 || !is_ints64;
    else if constexpr( arm_tag<current_api_type> )  return !is_ints64;
    else return true;
  }
};

// -----  Regular
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
EVE_FORCEINLINE auto
minmax_(EVE_SUPPORTS(cpu_), T0 v0, T1 v1, Ts... vs) noexcept
    -> decltype(kumi::tuple {eve::min(v0, v1, vs...), eve::max(v0, v1, vs...)})
{
  if constexpr( prefer_min_max<common_value_t<T0,T1,Ts...>>() )
  {
    return kumi::tuple {eve::min(v0, v1, vs...), eve::max(v0, v1, vs...)};
  }
  else
  {
    // If there is no native min/max, we compute the check once
    // We use > cause it is more often optimized than <
    auto check = v0 > v1;
    return kumi::tuple {if_else(check, v1, v0, vs...), if_else(check, v0, v1, vs...)};
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
    return [](auto x, auto y) { return kumi::reorder<1,0>(minmax(x,y)); };
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
