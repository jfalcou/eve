//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace eve::detail
{
  // Values list helper
  template<auto... Values>
  struct values
  {
    static constexpr auto size = sizeof...(Values);
  };

  // Types list helper
  template<typename... Types>
  struct types
  {
    template<typename... Us> constexpr types<Types...,Us...> operator+( types<Us...> const&) const;
  };

  // Concatenate types lists
  template<typename... Ls> struct concatenate
  {
    using type = decltype( (Ls{} + ...) );
  };

  template<typename... Ls>
  using concatenate_t = typename concatenate<Ls...>::type;

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
  struct upgrader
  {
    using type = T;
  };

  template < typename T>
  struct upgrader < T, true>
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
  struct upgrader< T, false>
  {
    using type = double;
  };

  template<typename T>
  struct upgrade : upgrader<T>
  {
  };

  template<typename T>
  using upgrade_t = typename upgrade<T>::type;


  //////////////////////////////////////////////////////
  // Downgrade a type (u)int(xx) -> (u)int(max(xx/2, 8)
  //                double -> float,  float -> float
  template < typename T, bool is = std::is_integral_v<T>>
  struct downgrader
  {
    using type = T;
  };

  template < typename T>
  struct downgrader < T, true>
  {
    template<std::size_t Size, bool Sign, typename Dummy = void>
    struct fetch;

    template<typename Dummy>
    struct fetch<1, true, Dummy>
    {
      using type = std::int8_t;
    };
    template<typename Dummy>
    struct fetch<2, true, Dummy>
    {
      using type = std::int8_t;
    };
    template<typename Dummy>
    struct fetch<4, true, Dummy>
    {
      using type = std::int16_t;
    };
    template<typename Dummy>
    struct fetch<8, true, Dummy>
    {
      using type = std::int32_t;
    };

    template<typename Dummy>
    struct fetch<1, false, Dummy>
    {
      using type = std::uint8_t;
    };
    template<typename Dummy>
    struct fetch<2, false, Dummy>
    {
      using type = std::uint8_t;
    };
    template<typename Dummy>
    struct fetch<4, false, Dummy>
    {
      using type = std::uint16_t;
    };
    template<typename Dummy>
    struct fetch<8, false, Dummy>
    {
      using type = std::uint32_t;
    };

    using sel = fetch<sizeof(T), std::is_signed_v<T>>;
    using type = typename sel::type;

  };

//   template < typename T>
//   struct downgrader< T, false>
//   {
//     using type = float;
//   };

  template<typename T>
  struct downgrade : downgrader<T>
  {
  };

  template<typename T>
  using downgrade_t = typename downgrade<T>::type;

  ///////////////////////////////////////////////////////////////////

  // Extract the sign of a type
  template<typename T>
  struct sign_of : std::conditional<std::is_signed_v<value_type_t<T>>, signed, unsigned>
  {
  };

  template<typename T>
  using sign_of_t = typename sign_of<T>::type;

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

  // false_ value with dependent type
  template<typename... T>
  inline constexpr bool wrong = false;

  // Turns a pseudo-concept into a traits
  template<template<class...> class Concept, typename List, typename Enable = void>
  struct as_trait_impl : std::false_type
  {};

  template<template<class...> class Concept,typename... T>
  struct as_trait_impl<Concept, types<T...>, std::void_t<Concept<T...>> > : std::true_type
  {};

  template<template<class...> class Concept,typename... T>
  struct as_trait : as_trait_impl<Concept, types<T...>>
  {};

  // Tuple free apply
  template<std::size_t Count, typename Func> EVE_FORCEINLINE decltype(auto) apply(Func &&f)
  {
    const auto impl = [&]<std::size_t... I>(std::index_sequence<I...> const &)
    {
      return std::forward<Func>(f)(std::integral_constant<std::size_t, I>{}...);
    };

    return impl(std::make_index_sequence<Count>{});
  }

  // Tuple free apply from generator data
  template<template<auto...> class Generator, auto... I, typename Func>
  EVE_FORCEINLINE decltype(auto) apply(Func &&f, Generator<I...> const& g)
  {
    const auto impl = [&](Generator<I...> const &)
    {
      return std::forward<Func>(f)(std::integral_constant<std::size_t, I>{}...);
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
                  return f(std::integral_constant<type, N::value*Step>{} );
                };

    [&]<auto... Iter>( std::integer_sequence<type,Iter...> )
    {
      ( body( std::integral_constant<type,Iter>{} ), ...);
    }( std::make_integer_sequence<type,End - Begin>{});
  }

  template<auto Begin, auto Step, auto End, typename Func>
  EVE_FORCEINLINE constexpr bool for_until_(Func f)
  {
    using type = decltype(Begin);

    return [&]<auto... Iter>( std::integer_sequence<type,Iter...> )
    {
      return ( f(std::integral_constant<type, Iter * Step>{} ) || ...);
    }( std::make_integer_sequence<type,End - Begin>{});
  }
}
