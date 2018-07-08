//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_META_IS_RANGE_HPP_INCLUDED
#define EVE_DETAIL_META_IS_RANGE_HPP_INCLUDED

#include <iterator>
#include <type_traits>

namespace eve { namespace detail
{
  // Detect if a Type behaves a Range
  template <typename T> struct is_range_impl
  {
    static std::false_type test(...);

    template <  typename U
              , typename=decltype(std::begin(std::declval<U>()))
              , typename=decltype(std::end  (std::declval<U>()))
              >
    static std::true_type test(U&&);

    static constexpr auto value = std::is_same_v<decltype(test(std::declval<T>())),std::true_type>;
  };

  template<typename T>
  inline constexpr bool is_range_v = detail::is_range_impl<T>::value;

  template<typename T>
  struct is_range : std::bool_constant<is_range_v<T>> {};

  template<typename T>
  using is_range_t = typename is_range<T>::type;

  // Detect if a Type behaves a Random Access Range
  template <typename T> struct is_rarange_impl
  {
    static std::false_type test(...);

    template <  typename U
              , typename=decltype(std::begin(std::declval<U>()))
              , typename=decltype(std::end  (std::declval<U>()))
              , typename=decltype(std::declval<U>()[0])
              >
    static std::true_type test(U&&);

    static constexpr auto value = std::is_same_v<decltype(test(std::declval<T>())),std::true_type>;
  };

  template<typename T>
  inline constexpr bool is_random_access_range_v = detail::is_rarange_impl<T>::value;

  template<typename T>
  struct is_random_access_range : std::bool_constant<is_random_access_range_v<T>> {};

  template<typename T>
  using is_random_access_range_t = typename is_random_access_range<T>::type;
} }

#endif
