//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_ATAN2PI_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_ATAN2PI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct atan2pi_; }
  
  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::atan2pi_), T const&, U const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>; 
      if constexpr(is_vec_t)
        static_assert ( std::is_floating_point_v<value_type_t<T>>,
                        "[eve::atan2pi] - No support for integral types"
                      );
      if constexpr(is_vec_u)
        static_assert ( std::is_floating_point_v<value_type_t<U>>,
                        "[eve::atan2pi] - No support for integral types"
                      );
      if constexpr(!is_vec_t && !is_vec_u)
      {
        static_assert ( std::is_floating_point_v<value_type_t<T>>,
                        "[eve::atan2dpi - No support for integral types"
                      );
        static_assert ( std::is_floating_point_v<value_type_t<U>>,
                        "[eve::atan2pi] - No support for integral types"
                      );
      }      
    }
    
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(pedantic_type, eve::tag::atan2pi_), T const&, U const &)
    {
      constexpr bool is_vec_t = is_vectorized_v<T>;
      constexpr bool is_vec_u = is_vectorized_v<U>; 
      if constexpr(is_vec_t)
        static_assert ( std::is_floating_point_v<value_type_t<T>>,
                        "[eve::pedantic_(eve::atan2pi)] - No support for integral types"
                      );
      if constexpr(is_vec_u)
        static_assert ( std::is_floating_point_v<value_type_t<U>>,
                        "[eve::pedantic_(eve::atan2pi)] - No support for integral types"
                      );
      if constexpr(!is_vec_t && !is_vec_u)
      {
        static_assert ( std::is_floating_point_v<value_type_t<T>>,
                        "[eve::pedantic_(eve::atan2pi)] - No support for integral types"
                      );
        static_assert ( std::is_floating_point_v<value_type_t<U>>,
                        "[eve::pedantic_(eve::atan2pi)] - No support for integral types"
                      );
      }
    }
  }
  
  EVE_MAKE_CALLABLE(atan2pi_, atan2pi);
}

#endif
