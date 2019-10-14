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
  using convertible = std::enable_if_t<std::is_convertible_v<From, To>>;

  template<typename T>
  using arithmetic = std::enable_if_t<std::is_arithmetic_v<T>>;

  template<typename T>
  using integral = std::enable_if_t<std::is_integral_v<T>>;

  template<typename T>
  using floating = std::enable_if_t<std::is_floating_point_v<T>>;

  template<bool... Conditions>
  using either = std::enable_if_t<(Conditions || ...)>;

  template< template<class...> class Concept, typename... Ts>
  using behave_as = Concept< value_type_t<Ts>... >;

  template<typename T, typename U>
  using bitwise_compatible = std::enable_if_t
                              < (sizeof(U) == sizeof(T)) ||
                                (     (cardinal_v<U> == 1 || cardinal_v<T> == 1)
                                  &&  (sizeof(value_type_t<U>) == sizeof(value_type_t<T>))
                                )
                              >;
}

#endif
