//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_NEXT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_NEXT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/is_gez.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct next_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::next_), saturated_type const &, T const&,  U const & n)
    {
      static_assert(std::is_integral_v<value_type_t<U>>, "[saturated_(next)] : second parameter must be of integral type");
      EVE_ASSERT(all(is_gez(n)), "[next] : second parameter must be positive"); 
    }
    
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::next_), T const&,  U const & n)
    {
      static_assert(std::is_integral_v<value_type_t<U>>, "[next] : second parameter must be of integral type");
      EVE_ASSERT(all(is_gez(n)), "[next] : second parameter must be positive"); 
    }
  }

  EVE_MAKE_CALLABLE(next_, next);
}

#endif
