//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BITWISE_SELECT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BITWISE_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct bitwise_select_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::bitwise_select_), T const&, U const &, U const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>; 
      if constexpr(!is_vec_t && is_vec_u)
      {
        static_assert(sizeof(T) == sizeof(value_type_t<U>),
                    "[eve::bitwise_select]  - scalar argument has not the same size as the vector element");

      }
      else  if constexpr(is_vec_t && !is_vec_u)
      {
        static_assert(sizeof(U) == sizeof(value_type_t<T>),
                    "[eve::bitwise_select]  - scalar argument has not the same size as the vector element");

      }
      else 
      {
        static_assert(sizeof(U) == sizeof(T),
                    "[eve::bitwise_select]  -  arguments has not the same global size");
      }
    }
  }
  
  EVE_MAKE_CALLABLE(bitwise_select_, bitwise_select);
}

#endif
