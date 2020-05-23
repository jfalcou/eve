//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_COMBINE_HPP_INCLUDED
#define EVE_FUNCTION_COMBINE_HPP_INCLUDED

#include <eve/function/definition/combine.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/as_wide.hpp>

namespace eve::detail
{
  template<value T> EVE_FORCEINLINE auto combine_(EVE_SUPPORTS(cpu_),T const &a,T const &b) noexcept
  {
    return as_wide_t<T, typename cardinal_t<T>::combined_type>(a, b);
  }
}

#endif
