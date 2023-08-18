//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/shuffle_v2_fwd.hpp>

namespace eve::detail
{

/*
 * A heler for functions that are just shuffles one register with a different interface.
 * The only benefit is that we can do testing infrastructure once.
 *
 * You have to provide 1 function pattern(args...) - where args is the extra
 * arguments you need.
 *
 * We also have a `level` function that is only used in tests and for documentation
 * Level does not have to care for:
 *  * emulation
 *  * patterns of 1 elemenmt
 *
 * struct shuffle_name_t : detail::named_shuffle_1<shuffle_name_t>
 * {
 *   template <simd_value T, std::ptrdiff_t G>
 *   static constexpr std::ptrdiff_t level(eve::as<T>, eve::fixed<G>, auto ...args)
 *   {
 *     //
 *     return 2;
 *   }
 *
 *   static constexpr auto pattern(eve::at<T>, eve::fixed<G>, auto ... args)
 *   {
 *     return eve::fix_pattern<T::size() / G>([](int i, int size) {...});
 *   }
 * } inline constexpr shuffle_name
 */

template<typename Name> struct named_shuffle_1 : Name
{
  template<simd_value T, std::ptrdiff_t G, typename... Args>
  EVE_FORCEINLINE auto operator()(T x, eve::fixed<G> g, Args... args) const
  requires requires { Name::pattern(eve::as<T> {}, g, args...); }
  {
    if constexpr( G <= 0 ) { static_assert(G > 0, "Group size <= 0 is not supported"); }
    else return shuffle_v2(x, g, Name::pattern(eve::as<T> {}, g, args...));
  }

  template<simd_value T, typename... Args>
  EVE_FORCEINLINE auto operator()(T x, Args... args) const
  requires requires { Name::pattern(eve::as<T> {}, eve::lane<1>, args...); }
  {
    return operator()(x, eve::lane<1>, args...);
  }
};

template<typename Name> struct named_shuffle_2 : Name
{
  template<simd_value T, std::ptrdiff_t G, typename... Args>
  EVE_FORCEINLINE auto operator()(T x, T y, eve::fixed<G> g, Args... args) const
  requires requires { Name::pattern(eve::as<T> {}, eve::as<T> {}, g, args...); }
  {
    if constexpr( G <= 0 ) { static_assert(G > 0, "Group size <= 0 is not supported"); }
    else return shuffle_v2(x, y, g, Name::pattern(eve::as<T> {}, eve::as<T> {}, g, args...));
  }

  template<simd_value T, typename... Args>
  EVE_FORCEINLINE auto operator()(T x, T y, Args... args) const
  requires requires { Name::pattern(eve::as<T> {}, eve::as<T> {}, eve::lane<1>, args...); }
  {
    return operator()(x, y, eve::lane<1>, args...);
  }
};

}
