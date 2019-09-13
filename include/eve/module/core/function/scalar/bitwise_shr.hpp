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
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bitwise_shr_(EVE_SUPPORTS(cpu_), T const &a0, U a1) noexcept requires(T, Integral<U>, Integral<T>)
  {
    using u_t = eve::detail::as_integer_t<T, unsigned>;
    return T(u_t(a0) >> a1);
  }
}

#endif
