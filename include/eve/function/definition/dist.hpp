//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_DIST_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_DIST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>


namespace eve
{
 namespace tag { struct dist_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::dist_), T const&, U const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>; 
      if constexpr(is_vec_t && is_vec_u)
      {
        static_assert(std::is_same_v<T, U>,
                    "[eve::dist]  - SIMD arguments have not the same type");
      }
    }
  
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::dist_), T const&, U const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>; 
      if constexpr(is_vec_t && is_vec_u)
      {
        static_assert(std::is_same_v<T, U>,
                    "[eve::dist]  - SIMD arguments have not the same type");
      }
    }
  }

  EVE_MAKE_CALLABLE(dist_, dist);
}

#endif
