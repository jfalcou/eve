//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_COPYSIGN_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_COPYSIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/cardinal.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct copysign_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::copysign_), T const&, U const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>; 
      static_assert(std::is_same_v<value_type_t<U>, value_type_t<T>>,
                    "[eve::copysign]  - value types must be the same");
      if constexpr(is_vec_t && is_vec_u)
      {
        static_assert(cardinal_v<U> == cardinal_v<T>,
                      "[eve::copysign]  - cannot copysign on types of different cardinal");
        
      }
    }
  }
  
  EVE_MAKE_CALLABLE(copysign_, copysign);
}

#endif
