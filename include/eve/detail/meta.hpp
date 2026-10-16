//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/deps/kumi.hpp>
#include <eve/arch/float16.hpp>

#include <type_traits>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace eve::_
{
  // Generate integral types from sign + size
  template<std::size_t Size, typename Sign = unsigned>
  extern undefined<> make_integer;

  template<> inline std::int8_t  make_integer<1, signed>{};
  template<> inline std::int16_t make_integer<2, signed>{};
  template<> inline std::int32_t make_integer<4, signed>{};
  template<> inline std::int64_t make_integer<8, signed>{};

  template<> inline std::uint8_t  make_integer<1, unsigned>{};
  template<> inline std::uint16_t make_integer<2, unsigned>{};
  template<> inline std::uint32_t make_integer<4, unsigned>{};
  template<> inline std::uint64_t make_integer<8, unsigned>{};

  template<std::size_t Size, typename Sign = unsigned>
  using make_integer_t = decltype(make_integer<Size, Sign>);

  // Generate floating point types from sign + size
  template<std::size_t Size> extern undefined<> make_floating_point;
  template<> inline eve::float16_t make_floating_point<2>{};
  template<> inline float make_floating_point<4>{};
  template<> inline double make_floating_point<8>{};

  template<std::size_t Size>
  using make_floating_point_t = decltype(make_floating_point<Size>);

  // Tuple free apply
  template<std::size_t Count, typename Func> EVE_FORCEINLINE decltype(auto) apply(Func &&f)
  {
    const auto impl = [&]<std::size_t... I>(std::index_sequence<I...> const &)
      {
        return EVE_FWD(f)(std::integral_constant<std::size_t, I>{}...);
      };

    return impl(std::make_index_sequence<Count>{});
  }

  // Tuple free apply from generator data
  template<template<auto...> class Generator, auto... I, typename Func>
  EVE_FORCEINLINE decltype(auto) apply(Func &&f, Generator<I...> const& g)
  {
    const auto impl = [&](Generator<I...> const &)
      {
        return EVE_FWD(f)(std::integral_constant<std::size_t, I>{}...);
      };

    return impl(g);
  }

  // Find the index of the first Ps equals to p
  template<typename P, typename... Ps>
  consteval std::ptrdiff_t find_index(P p, kumi::tuple<Ps...> )
  {
    bool checks[] = { (Ps{} == p)...};
    for(std::size_t i=0;i<sizeof...(Ps);++i) if(checks[i]) return i;
    return -1;
  }

  // Reusable for-loop like meta-function
  template<auto Begin, auto Step, auto End, typename Func>
  EVE_FORCEINLINE constexpr void for_(Func f)
  {
    using type = decltype(Begin);
    auto body = [&]<typename N>(N)
      {
        return f(std::integral_constant<type, Begin + N::value*Step>{} );
      };

    [&]<auto... Iter>( std::integer_sequence<type,Iter...> )
    {
      ( body( std::integral_constant<type,Iter>{} ), ...);
    }( std::make_integer_sequence<type, (End - Begin + Step - 1) / Step>{});
  }

  // Can't use a lambda because need to force inline
  template <auto Begin, auto Step, decltype(Begin) ... Iter, typename Func>
  EVE_FORCEINLINE constexpr bool for_until_impl_(
    std::integer_sequence<decltype(Begin), Iter...>, Func& f)
  {
    return ( f(std::integral_constant<decltype(Begin), Begin + Iter * Step>{} ) || ...);
  }

  template<auto Begin, auto Step, auto End, typename Func>
  EVE_FORCEINLINE constexpr bool for_until_(Func f)
  {
    return for_until_impl_<Begin, Step>(std::make_integer_sequence<decltype(Begin), (End - Begin + Step - 1) / Step>{}, f);
  }
}
