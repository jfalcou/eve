//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_ULP_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_ULP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct ulp_; }

  namespace detail
  {
   
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::ulp_), T const&,  U const & n)
    {
        EVE_ASSERT(all(is_gez(n)), "[eve::ulp] : second parameter must be positive"); 
    } 
    
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::ulp_), T const&,  U const & n)
    {
      EVE_ASSERT(all(is_gez(n)), "[[eve::saturated_([eve::ulp)] : second parameter must be positive");
    }
  }

  EVE_MAKE_CALLABLE(ulp_, ulp);
}

#endif
