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
#include <eve/assert.hpp>

namespace eve
{
  namespace tag { struct clamp_; }

  namespace detail
  {
    template<typename X, typename L, typename H>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::clamp_), X const&, L const& lo, H const& hi)
    {
      EVE_ASSERT(assert_all(lo <= hi), "[eve::clamp] Unordered clamp boundaries");
    }
  }

  EVE_MAKE_CALLABLE(clamp_, clamp);
}

#endif
