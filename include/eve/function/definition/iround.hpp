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
#include <type_traits>
#include <eve/function/roundings.hpp>

namespace eve
{
   namespace tag { struct iround_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::iround_), T const&,  U const &)
    {
      static_assert ( std::is_same_v<U, eve::upward_type> || std::is_same_v<U, eve::downward_type>
                      || std::is_same_v<U, eve::toward_zero_type> || std::is_same_v<U, eve::to_nearest_type>,
                      "[eve::iround] - second parameter must be one of the following:  eve::upward_ or  eve::downward_ or eve::toward_zero_ or _eve::to_nearest_"
                    );
    }
  }

  EVE_MAKE_CALLABLE(iround_, iround);
}

