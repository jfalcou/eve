//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_SQRT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_SQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct sqrt_; }

  namespace detail
  {
    template<typename T> EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::sqrt_), T const& v)
    {
      if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
      {
        EVE_ASSERT(v >= 0, "[eve::sqrt] - Invalid parameter: " << v );
      }
    }
  }

  EVE_MAKE_CALLABLE(sqrt_, sqrt);
}

#endif
