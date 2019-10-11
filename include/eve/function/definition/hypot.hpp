//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_HYPOT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_HYPOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct hypot_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::hypot_), T const&, U const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>;
      
      if constexpr(is_vec_t)
      {
        static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::hypot] - No support for SIMD integral types"
                      );
      }
      if constexpr(is_vec_u)
      {
        static_assert ( std::is_floating_point_v<value_type_t<U>>,
                      "[eve::hypot] - No support for SIMD integral types"
                      );
      }
      if constexpr(is_vec_t && is_vec_u)
      {
        static_assert(std::is_same_v<T, U>,
                    "[eve::hypot]  - SIMD arguments have not the same type");

      }
      else  if constexpr(!is_vec_t && !is_vec_u)
      {
        static_assert(std::is_same_v<T, U>,
                    "[eve::hypot]  - scalar argument has not the same types");
      }
    }
  }
  
  EVE_MAKE_CALLABLE(hypot_, hypot);
}

#endif
