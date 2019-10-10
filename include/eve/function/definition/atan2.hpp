//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_ATAN2_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_ATAN2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/pedantic.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct atan2_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::atan2_), T const&, U const &)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::atan2] - No support for integral types"
                    );
      static_assert ( std::is_floating_point_v<value_type_t<U>>,
                      "[eve::atan2] - No support for integral types"
                    );
    }

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(pedantic_type, eve::tag::atan2_), T const&, U const &)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::pedantic_(eve::atan2)] - No support for integral types"
                    );
      static_assert ( std::is_floating_point_v<value_type_t<U>>,
                      "[eve::pedantic_(eve::atan2)] - No support for integral types"
                    );
    }
  }

  EVE_MAKE_CALLABLE(atan2_, atan2);
}

#endif
