//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_META_IS_ITERATOR_HPP_INCLUDED
#define EVE_DETAIL_META_IS_ITERATOR_HPP_INCLUDED

#include <iterator>
#include <type_traits>

namespace eve { namespace detail
{
  template <typename T> struct is_iterator_impl
  {
    static std::false_type test(...);

    template <  typename U
              , typename=typename std::iterator_traits<U>::difference_type
              , typename=typename std::iterator_traits<U>::pointer
              , typename=typename std::iterator_traits<U>::reference
              , typename=typename std::iterator_traits<U>::value_type
              , typename=typename std::iterator_traits<U>::iterator_category
              >
    static std::true_type test(U&&);

    static constexpr auto value = std::is_same_v<decltype(test(std::declval<T>())),std::true_type>;
  };

  template<typename T>
  inline constexpr bool is_iterator_v = detail::is_iterator_impl<T>::value;

  template<typename T>
  struct is_iterator : std::bool_constant<is_iterator_v<T>> {};

  template<typename T>
  using is_iterator_t = typename is_iterator<T>::type;
} }

#endif
