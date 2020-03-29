//==================================================================================================
/**v
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_TWO_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_TWO_ADD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/add.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <tuple>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto two_add_(EVE_SUPPORTS(cpu_)
                                 , const T& a
                                 , const T& b) noexcept
  {
    if constexpr(native<T>)
    {
      T r0 = a + b;
      T z = r0 - a;
      T r1 = a-(r0-z)+(b-z);
      if constexpr(eve::platform::supports_infinites)
        r1 = if_else(is_infinite(r0), eve::zero_, r1);
      return std::make_tuple(r0, r1);
    }
    else return apply_over2(two_add, a, b); 
  }
}

#endif
