//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_CLAMP_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_CLAMP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/abi.hpp>
#include <eve/assert.hpp>

namespace eve
{
  namespace tag { struct clamp_; }

  namespace detail
  {
    template<typename X, typename L, typename H>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::clamp_), X const&, L const& lo, H const& hi)
    {
      constexpr bool is_vec_t = is_vectorized_v<X>;
      if constexpr(!is_vec_t)
      {
        static_assert ( std::is_same_v<X, L> && std::is_same_v<X, H>
                      , "[eve::clamp scalar] - Incompatible types.");
      }
      else
      {
        if constexpr(is_vectorized_v<L>)
          static_assert ( std::is_same_v<X, L>
                        , "[eve::clamp SIMD] - Incompatible first and second parameters types.");
        else
          static_assert ( std::is_same_v<value_type_t<X>, L>
                        , "[eve::clamp SIMD] - Incompatible first and second parameters types.");
          
        if constexpr(is_vectorized_v<H>)
          static_assert ( std::is_same_v<X, H>
                        , "[eve::clamp SIMD] - Incompatible first and third parameters types.");         
        else
          static_assert ( std::is_same_v<value_type_t<X>, H>
                        , "[eve::clamp SIMD] - Incompatible first and third parameters types.");
      }
      
      EVE_ASSERT(assert_all(lo <= hi), "[eve::clamp] Unordered clamp boundaries");
    }
  }

  EVE_MAKE_CALLABLE(clamp_, clamp);
}

#endif
