//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

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
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rshl_), T const&, [[ maybe_unused ]]S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(eve::abs(s)),
                  "[eve::rshl] - Shifting by " << s
                  << " is out of the range ]"
                  << -int(sizeof(value_type_t<T>) * 8)
                  << ", "
                  << sizeof(value_type_t<T>) * 8
                  << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(rshl_, rshl);
}

