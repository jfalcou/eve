//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_IS_ITERATOR_HPP_INCLUDED
#define EVE_DETAIL_IS_ITERATOR_HPP_INCLUDED

#include <type_traits>

namespace eve::detail
{
  template<typename T, typename Enable = void>
  struct is_iterator : std::false_type
  {
  };

  template<typename T>
  struct is_iterator<T,
                     std::void_t<decltype(*std::declval<T>()) // Dereferenceable
                                 ,
                                 decltype(std::declval<T &>()++) // WeaklyIncrementable
                                 ,
                                 decltype(++std::declval<T &>())>> : std::true_type
  {
  };

  template<typename T>
  inline constexpr bool is_iterator_v = is_iterator<T>::value;
  template<typename T>
  using is_iterator_t = typename is_iterator<T>::type;
}

#endif
