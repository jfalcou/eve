//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_IS_RANGE_HPP_INCLUDED
#define EVE_DETAIL_IS_RANGE_HPP_INCLUDED

#include <iterator>
#include <type_traits>

namespace eve::detail
{
  // Detect if a Type behaves a Range
  template<typename T, typename Enable = void>
  struct is_range : std::false_type
  {
  };

  template<typename T>
  struct is_range<
      T,
      std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>>
      : std::true_type
  {
  };

  template<typename T>
  inline constexpr bool is_range_v = is_range<T>::value;
  template<typename T>
  using is_range_t = typename is_range<T>::type;

  // Detect if a Type behaves a Random Access Range
  template<typename T, typename Enable = void>
  struct is_random_access_range : std::false_type
  {
  };

  template<typename T>
  struct is_random_access_range<T,
                                std::void_t<decltype(std::begin(std::declval<T>())),
                                            decltype(std::end(std::declval<T>())),
                                            decltype(std::declval<T>()[ 0 ])>> : std::true_type
  {
  };

  template<typename T>
  inline constexpr bool is_random_access_range_v = is_random_access_range<T>::value;

  template<typename T>
  using is_random_access_range_t = typename is_random_access_range<T>::type;
}

#endif
