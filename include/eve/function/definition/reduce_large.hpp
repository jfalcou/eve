//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_REDUCE_LARGE_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_REDUCE_LARGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_gez.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct reduce_large_; }

  namespace detail
  {
   
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::reduce_large_), T const& x)
    {
      EVE_ASSERT(all(is_gez(x)), "[eve::reduce_large] :  parameter must be positive, found:" << x); 
    } 
 }
  
  EVE_MAKE_CALLABLE(reduce_large_, reduce_large);
}

#endif
