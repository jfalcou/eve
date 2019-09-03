//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_SHR_HPP_INCLUDED

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
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bitwise_shr_(EVE_SUPPORTS(cpu_), T const &a0, U a1) noexcept requires(T, Integral<U>, Integral<T>)
  {
    EVE_ASSERT(detail::assert_good_shift<T>(a1),
               "[ eve::bitwise_shr] scalar - Shift " << a1 << " is out of the range [0, "
                                                     << sizeof(T) * 8 << "[.");
    using u_t = eve::detail::as_integer_t<T, unsigned>;
    return T(u_t(a0) >> a1);
  }
}

#endif
