//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/rebindable.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace eve::detail
{
  // Value list helper
  template<auto... Values>
  struct values
  {
    static constexpr auto size = sizeof...(Values);
  };

  // Types list helper
  template<typename... Types>
  struct types
  {
  };

  // Return the first type in a type list matching a trait
  template<bool Done, template<typename> typename Pred, typename TL>
  struct first_with_impl;

  template<template<typename> typename Pred, typename TL>
  struct first_with;

  template<template<typename> typename Pred,typename T>
  struct first_with<Pred,types<T>> : std::conditional< Pred<T>::value, T, struct no_type_>
  {};

  template<template<typename> typename Pred,typename T>
  using first_with_t = typename first_with<Pred,T>::type;

  template<template<typename> typename Pred,typename T,typename... Ts>
  struct first_with_impl<true,Pred,types<T,Ts...>>
  {
    using type = T;
  };

  template<template<typename> typename Pred,typename T,typename... Ts>
  struct first_with_impl<false,Pred,types<T,Ts...>>
    : first_with<Pred,types<Ts...>>
  {};

  template<template<typename> typename Pred,typename T,typename... Ts>
  struct  first_with<Pred,types<T,Ts...>>
    : first_with_impl<Pred<T>::value,Pred,types<T,Ts...>>
  {};

// Check if a type is contained in a types list
  template<typename T, typename... Ts>
  constexpr bool is_one_of(types<Ts...> const&) noexcept
  {
    bool found[] = { std::is_same_v<T,Ts>... };

    return [&]<std::size_t... I>( std::index_sequence<I...> const&)
    {
      return (false || ... || found[I]);
    }( std::make_index_sequence<sizeof...(Ts)>{} );
  }

  // Type identity
  template<typename T>
  struct always
  {
    using type = T;
  };

  // Return the Nth type from a list of types
  template<std::size_t> struct anything { anything(...) {} };

  template<std::size_t... Is> struct nth
  {
    template<typename T> static auto fit(anything<Is>..., T, ...) -> T;
  };

  template<std::size_t... Is, typename... Ts>
  auto deduce(std::index_sequence<Is...>, Ts... pp) -> decltype( nth<Is...>::fit(pp...) );

  template<std::size_t N, typename Ts> struct type_at;

  template<std::size_t N, typename... Ts>
  struct type_at<N,types<Ts...>>
  {
    using type = decltype( deduce(std::make_index_sequence<N>{},Ts()...) );
  };

  // Extract value_type from type
  template<typename T> struct value_type
  {
    using type = T;
  };

  template<typename T>
  requires requires { typename T::value_type; }
  struct value_type<T>
  {
    using type = typename T::value_type;
  };

  template<typename T>
  using value_type_t    = typename value_type<T>::type;

  // Extract abi_type from type
  template<typename T, typename Enable = void>
  struct abi_type
  {
    using type = void;
  };

  template<typename T>
  struct abi_type<T, std::void_t<typename T::abi_type>>
  {
    using type = typename T::abi_type;
  };

  template<typename T>
  using abi_type_t = typename abi_type<T>::type;

  // Generate integral types from sign + size
  template<std::size_t Size, typename Sign = unsigned>
  struct make_integer;

  template<>
  struct make_integer<1, signed>
  {
    using type = std::int8_t;
  };
  template<>
  struct make_integer<2, signed>
  {
    using type = std::int16_t;
  };
  template<>
  struct make_integer<4, signed>
  {
    using type = std::int32_t;
  };
  template<>
  struct make_integer<8, signed>
  {
    using type = std::int64_t;
  };
  template<>
  struct make_integer<1, unsigned>
  {
    using type = std::uint8_t;
  };
  template<>
  struct make_integer<2, unsigned>
  {
    using type = std::uint16_t;
  };
  template<>
  struct make_integer<4, unsigned>
  {
    using type = std::uint32_t;
  };
  template<>
  struct make_integer<8, unsigned>
  {
    using type = std::uint64_t;
  };

  template<std::size_t Size, typename Sign = unsigned>
  using make_integer_t = typename make_integer<Size, Sign>::type;

  // Upgrade a type (u)int(xx) -> (u)int(min(2xx, 64)
  //                float -> double,  double -> double
  template < typename T, bool is = std::is_integral_v<T>>
  struct upgrade
  {
    using type = T;
  };

  template < typename T>
  struct upgrade < T, true>
  {
    template<std::size_t Size, bool Sign, typename Dummy = void>
    struct fetch;

    template<typename Dummy>
    struct fetch<1, true, Dummy>
    {
      using type = std::int16_t;
    };
    template<typename Dummy>
    struct fetch<2, true, Dummy>
    {
      using type = std::int32_t;
    };
    template<typename Dummy>
    struct fetch<4, true, Dummy>
    {
      using type = std::int64_t;
    };
    template<typename Dummy>
    struct fetch<8, true, Dummy>
    {
      using type = std::int64_t;
    };

    template<typename Dummy>
    struct fetch<1, false, Dummy>
    {
      using type = std::uint16_t;
    };
    template<typename Dummy>
    struct fetch<2, false, Dummy>
    {
      using type = std::uint32_t;
    };
    template<typename Dummy>
    struct fetch<4, false, Dummy>
    {
      using type = std::uint64_t;
    };
    template<typename Dummy>
    struct fetch<8, false, Dummy>
    {
      using type = std::uint64_t;
    };

    using sel = fetch<sizeof(T), std::is_signed_v<T>>;
    using type = typename sel::type;

  };

  template < typename T>
  struct upgrade < T, false>
  {
    using type = double;
  };

  template<typename T>
  using upgrade_t = typename upgrade<T>::type;

  // Extract the sign of a type
  template<typename T>
  struct sign_of : std::conditional<std::is_signed_v<value_type_t<T>>, signed, unsigned>
  {
  };

  template<typename T>
  using sign_of_t = typename sign_of<T>::type;

  // Turn a type into an integer one
  template<typename T, typename Sign = sign_of_t<T>>
  struct as_integer
  {
    using type = make_integer_t<sizeof(T), Sign>;
  };

  template<typename T, typename Sign = sign_of_t<T>>
  using as_integer_t = typename as_integer<T, Sign>::type;

  // Generate integral types from sign + size
  template<std::size_t Size>
  struct make_floating_point;

  template<>
  struct make_floating_point<4>
  {
    using type = float;
  };

  template<>
  struct make_floating_point<8>
  {
    using type = double;
  };

  template<std::size_t Size>
  using make_floating_point_t = typename make_floating_point<Size>::type;

  // Turn a type into an floating_point point one
  template<typename T>
  struct as_floating_point : make_floating_point<(sizeof(T) <= 4) ? 4: sizeof(T)>
  {};

  template<typename T>
  using as_floating_point_t = typename as_floating_point<T>::type;

  // false_ value with dependent type
  template<typename... T>
  inline constexpr bool wrong = false;

  // How manything items in tuple-like things ? 0 means non-tuple
  template<typename T>
  struct count : std::integral_constant<std::size_t,0>
  {};

  template<typename T> requires( rebindable<T> )
  struct count<T> : std::tuple_size<T>
  {};

  template<typename T>
  inline constexpr auto count_v = count<T>::value;

  // Tuple free apply
  template<std::size_t Count, typename Func> EVE_FORCEINLINE decltype(auto) apply(Func &&f)
  {
    const auto impl = [&]<std::size_t... I>(std::index_sequence<I...> const &)
    {
      return std::forward<Func>(f)(std::integral_constant<std::size_t, I>{}...);
    };

    return impl(std::make_index_sequence<Count>{});
  }

  template<template<auto...> class Generator, auto... I, typename Func>
  EVE_FORCEINLINE decltype(auto) apply(Func &&f, Generator<I...> const& g)
  {
    const auto impl = [&](Generator<I...> const &)
    {
      return std::forward<Func>(f)(std::integral_constant<std::size_t, I>{}...);
    };

    return impl(g);
  }
}
