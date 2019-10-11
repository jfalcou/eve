//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_FNMS_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_FNMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve
{
 namespace tag { struct fnms_; }

  namespace detail
  {
    template<typename T, typename U, typename V>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::fnms_), T const&, U const &, V const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>;
      constexpr bool is_vec_v = is_vectorized_v<V>;
      if constexpr(is_vec_t && is_vec_u && is_vec_v)
      {
        static_assert(std::is_same_v<T, U> && std::is_same_v<T, V>, 
                    "[eve::fnms]  - SIMD arguments have not the same type");

      }
      if constexpr(!is_vec_t && !is_vec_u && !is_vec_v)
      {
        static_assert(std::is_same_v<T, U> && std::is_same_v<T, V>, 
                    "[eve::fnms]  - scalar arguments have not the same type");

      }
    }
  }

  EVE_MAKE_CALLABLE(fnms_, fnms);
}

#endif
