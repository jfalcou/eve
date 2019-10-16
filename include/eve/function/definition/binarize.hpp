//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BINARIZE_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BINARIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

namespace eve
{
   namespace tag { struct binarize_; }
  
  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::binarize_), T const&,  U const &)
    {
      static_assert ( is_vectorizable_v<U>|| std::is_same_v<U, eve::callable_mone_> || std::is_same_v<U, eve::callable_allbits_>,
                      "[eve::binarize] - second parameter must be scalar or eve::mone_ or eve::allbits_"
                    );
    }
  }

  EVE_MAKE_CALLABLE(binarize_, binarize);
}

#endif
