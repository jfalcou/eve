//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_ROUND_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_ROUND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/tags.hpp>

namespace eve
{
   namespace tag { struct round_; }
  
  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::round_), T const&,  U const &)
    {
      static_assert ( std::is_same_v<U, eve::upward_type> || std::is_same_v<U, eve::downward_type
                      || eve::toward_zero_type || eve::to_nearest_type>,
                      "[eve::round] - second parameter must be eve::upward_ or  eve::downward_ or eve::toward_zero_ or _eve::to_nearest_"
                    );
    }
  }

  EVE_MAKE_CALLABLE(round_, round);
}

#endif
