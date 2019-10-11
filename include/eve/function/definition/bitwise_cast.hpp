//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct bitwise_cast_; }
  
  namespace detail
  {
    template<typename T, typename Target>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::bitwise_cast_), T const&,  as_<Target> const &)
    {
      static_assert(sizeof(Target) == sizeof(T),
                    "[eve::bitwise_cast]  - vector arguments has not the same global size");
    }
  }

  EVE_MAKE_CALLABLE(bitwise_cast_, bitwise_cast);
}

#endif
