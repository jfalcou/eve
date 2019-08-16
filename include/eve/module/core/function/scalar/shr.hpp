//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/function/scalar/bitwise_cast.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T,  typename U>
  EVE_FORCEINLINE constexpr auto shr_(EVE_SUPPORTS(cpu_)
                                     , T const &a0
                                     , U const &a1) noexcept
  requires(T, Integral<U>,  Integral<T>)
  {
    EVE_ASSERT(detail::assert_good_shift<T>(a1),
               "[ eve::shl scalar] - Shift " << a1 << " is out of the range [0, "
                                                       << sizeof(T) * 8 << "[.");
    return T(a0 >>  a1);
  }
}

#endif
