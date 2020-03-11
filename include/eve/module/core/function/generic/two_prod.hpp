//==================================================================================================
/**v
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_TWO_PROD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_TWO_PROD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/add.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/two_split.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto two_prod_(EVE_SUPPORTS(cpu_)
                                 , const T& a
                                 , const T& b) noexcept
  {
    //enforce_precision<T> enforcer;
    auto [a1, a2] = two_split(a);
    auto [b1, b2] = two_split(b);
    T r0 = a*b;
    T r1 = a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2); 
    if constexpr(eve::platform::supports_invalids)
      r1 = if_else(is_not_finite(r0), eve::zero_, r1); 
    return std::make_tuple(r0, r1);
  }
}

#endif
