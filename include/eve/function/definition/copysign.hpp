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
#include <type_traits>

namespace eve
{
  namespace tag { struct copysign_; }
  
  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::copysign_), T const&, U const &)
    {
      static_assert(std::is_same_v<value_type_t<U>, value_type_t<T>>,
                    "[eve::copysign]  - value types must be the same");
    }
  }

EVE_MAKE_CALLABLE(copysign_, copysign);
}

#endif
