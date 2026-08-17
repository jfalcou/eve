//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/arch/float16.hpp>
#include <eve/as.hpp>

#include <type_traits>
#include <utility>
#include <cstdint>
#include <cstddef>

namespace eve::_
{
  // Types list helper
  template<typename... Types>
  struct types
  {
    template<typename... Us> constexpr types<Types...,Us...> operator+( types<Us...> const&) const;
  };

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


  ///////////////////////////////////////////////////////////////////

  // Generate integral types from sign + size
  template<std::size_t Size>
  struct make_floating_point;

  template<>
  struct make_floating_point<2>
  {
    using type = eve::float16_t;
  };

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

  // Tuple free apply from generator data
  template<std::size_t... I, typename Func>
  EVE_FORCEINLINE decltype(auto) apply(Func &&f, std::index_sequence<I...>)
  {
    return EVE_FWD(f)(std::integral_constant<std::size_t, I>{}...);
  }

  // Tuple free apply
  template<std::size_t Count, typename Func> EVE_FORCEINLINE decltype(auto) apply(Func &&f)
  {
    return apply(EVE_FWD(f), std::make_index_sequence<Count>{});
  }

  // Find the index of the first Ps equals to p
  template<typename P, typename... Ps>
  consteval std::ptrdiff_t find_index(P p, kumi::tuple<Ps...> )
  {
    bool checks[] = { (Ps{} == p)...};
    for(std::size_t i=0;i<sizeof...(Ps);++i) if(checks[i]) return i;
    return -1;
  }
 
  // Can't use a lambda because need to force inline
  template <auto Begin, auto Step, decltype(Begin) ... Iter, typename Func>
  EVE_FORCEINLINE constexpr void for_impl_(
    std::integer_sequence<decltype(Begin), Iter...>, Func& f)
  {
    return ( f(std::integral_constant<decltype(Begin), Begin + Iter * Step>{} ), ...);
  }

  // Reusable for-loop like meta-function
  template<auto Begin, auto Step, auto End, typename Func>
  EVE_FORCEINLINE constexpr void for_(Func f)
  {
    return for_impl_<Begin, Step>(std::make_integer_sequence<decltype(Begin), (End - Begin + Step - 1) / Step>{}>{}, f);
  }

  // Can't use a lambda because need to force inline
  template <auto Begin, auto Step, decltype(Begin) ... Iter, typename Func>
  EVE_FORCEINLINE constexpr bool for_until_impl_(
    std::integer_sequence<decltype(Begin), Iter...>, Func& f)
  {
    return ( f(std::integral_constant<decltype(Begin), Begin + Iter * Step>{} ) || ...);
  }

  // Reusable for_until-loop like meta-function
  template<auto Begin, auto Step, auto End, typename Func>
  EVE_FORCEINLINE constexpr bool for_until_(Func f)
  {
    return for_until_impl_<Begin, Step>(std::make_integer_sequence<decltype(Begin), (End - Begin + Step - 1) / Step>{}, f);
  }

  // instance concept
  template <typename T, template <typename ...> class Templ>
  struct instance_of_impl : std::false_type {};

  template <typename ...Args, template <typename ...> class Templ>
  struct instance_of_impl<Templ<Args...>, Templ> : std::true_type {};

  template <typename T, template <typename ...> class Templ>
  concept instance_of = instance_of_impl<std::remove_cvref_t<T>, Templ>::value;

  // one_of concept
  template<typename T, typename... Ts>
  concept one_of = (std::same_as<T,Ts> || ... || false);

  template <bool>
  struct conditional_impl_ {
      template <typename T, typename U>
      using type = U;
  };

  template <>
  struct conditional_impl_<true> {
      template <typename T, typename U>
      using type = T;
  };

  template <bool test, typename T, typename U>
  using conditional_t = conditional_impl_<test>:: template type<T, U>;
}
