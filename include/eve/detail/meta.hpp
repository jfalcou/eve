//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_META_HPP_INCLUDED
#define EVE_DETAIL_META_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <type_traits>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace eve::detail
{
  // Silence unused warning
  template<typename... T>
  void ignore(T &&...)
  {
  }

  // Types list helper
  template<typename... Types>
  struct types
  {
  };

  // Type identity
  template<typename T>
  struct always
  {
    using type = T;
  };

  // Normalize integral types to std::*int*_t types
  template<typename T>
  struct normalize
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
      using type = std::int16_t;
    };
    template<typename Dummy>
    struct fetch<4, true, Dummy>
    {
      using type = std::int32_t;
    };
    template<typename Dummy>
    struct fetch<8, true, Dummy>
    {
      using type = std::int64_t;
    };

    template<typename Dummy>
    struct fetch<1, false, Dummy>
    {
      using type = std::uint8_t;
    };
    template<typename Dummy>
    struct fetch<2, false, Dummy>
    {
      using type = std::uint16_t;
    };
    template<typename Dummy>
    struct fetch<4, false, Dummy>
    {
      using type = std::uint32_t;
    };
    template<typename Dummy>
    struct fetch<8, false, Dummy>
    {
      using type = std::uint64_t;
    };

    using selection = std::conditional_t<std::is_integral_v<T> && !std::is_same_v<T, bool>,
                                         fetch<sizeof(T), std::is_signed_v<T>>,
                                         always<T>>;

    using type = typename selection::type;
  };

  // Extract value_type from type
  template<typename T, typename Enable = void>
  struct value_type
  {
    using type = T;
  };

  template<typename T>
  struct value_type<T, std::void_t<typename T::value_type>>
  {
    using type = typename T::value_type;
  };

  template<typename T>
  using value_type_t = typename value_type<T>::type;

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
  struct as_floating_point
  {
    using type = make_floating_point_t<sizeof(T)>;
  };

  template<typename T>
  using as_floating_point_t = typename as_floating_point<T>::type;

  // Tuple free apply
  template<typename Func, std::size_t... I>
  EVE_FORCEINLINE decltype(auto) apply_impl(Func &&f, std::index_sequence<I...> const &)
  {
    return std::forward<Func>(f)(std::integral_constant<std::size_t, I>{}...);
  }

  template<std::size_t Count, typename Func>
  EVE_FORCEINLINE decltype(auto) apply(Func &&f)
  {
    return apply_impl(std::forward<Func>(f), std::make_index_sequence<Count>{});
  }

  // Recurrent pseudo-concept checkers
  template<typename R, typename Enabler>
  struct require_impl;
  template<typename R>
  struct require_impl<R, void>
  {
    using type = R;
  };

  template<typename Return, typename... Ts>
  struct require_check : require_impl<Return, std::void_t<Ts...>>
  {
  };

  template<typename From, typename To>
  using Convertible = std::enable_if_t<std::is_convertible_v<From, To>>;

  template<typename T>
  using Arithmetic = std::enable_if_t<std::is_arithmetic_v<T>>;

  template<typename T>
  using Integral = std::enable_if_t<std::is_integral_v<T>>;

  template<typename T>
  using Floating = std::enable_if_t<std::is_floating_point_v<T>>;

  template<bool Condition>
  using If = std::enable_if_t<Condition>;

  template<bool... Conditions>
  using Either = std::enable_if_t<(Conditions || ...)>;

  // False value with dependent type
  template<typename... T>
  inline constexpr bool wrong = false;
}

// Pseudo satisfy macro
#  define satisfy(...) typename ::eve::detail::require_check<void, __VA_ARGS__>::type * = nullptr

// Pseudo require macro
#  define requires(...)->typename ::eve::detail::require_check < __VA_ARGS__> ::type

#endif
