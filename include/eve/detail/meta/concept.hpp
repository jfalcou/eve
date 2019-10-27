//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_META_CONCEPT_HPP_INCLUDED
#define EVE_DETAIL_META_CONCEPT_HPP_INCLUDED

#include <eve/detail/meta/traits.hpp>
#include <eve/cardinal.hpp>
#include <type_traits>

namespace eve::detail
{
  template<bool Condition>
  using if_ = std::enable_if_t<Condition>;

  template<typename From, typename To>
  using same_as = std::enable_if_t<std::is_same_v<From, To>>;

  template<typename From, typename To>
  using convertible = std::enable_if_t<std::is_convertible_v<From, To>>;

  template<typename T>
  using arithmetic = std::enable_if_t<std::is_arithmetic_v<T>>;

  template<typename T>
  using integral = std::enable_if_t<std::is_integral_v<T>>;

  template<typename T>
  using floating_point = std::enable_if_t<std::is_floating_point_v<T>>;

  template<bool... Conditions>
  using either = std::enable_if_t<(Conditions || ...)>;

  template< template<class...> class Concept, typename... Ts>
  using behave_as = Concept< value_type_t<Ts>... >;

  template<typename T, typename U>
  using equality_comparable_with = std::void_t< decltype( std::declval<T>() == std::declval<U>() )>;

  template<typename T>
  using equality_comparable = equality_comparable_with<T,T>;

  template<typename T, typename U>
  using totally_ordered_with = std::void_t< equality_comparable_with<T,U>
                                     , decltype( std::declval<T>() < std::declval<U>() )
                                     , decltype( std::declval<T>() > std::declval<U>() )
                                     , decltype( std::declval<T>() <= std::declval<U>() )
                                     , decltype( std::declval<T>() >= std::declval<U>() )
                                     >;
 template<typename T>
  using totally_ordered= totally_ordered_with<T,T>;
  
}

#endif
