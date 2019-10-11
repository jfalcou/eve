//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_RSHL_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_RSHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/function/abs.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct rshl_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rshl_), T const& v, S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(abs(s)),
                  "[eve::rshl] Shifting by " << s
                  << " is out of the range ]"
                  << -sizeof(value_type_t<T>) * 8
                  << ", "                
                  << sizeof(value_type_t<T>) * 8
                  << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(rshl_, rshl);
}

#endif
