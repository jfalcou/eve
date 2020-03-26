//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/stdconcepts.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bit_shr_(EVE_SUPPORTS(cpu_), T const &a0, U a1) noexcept
  requires std::integral<U> && std::integral<T>
  {
    using u_t = eve::detail::as_integer_t<T, unsigned>;
    return static_cast<T>(u_t(a0) >> a1);
  }
}

#endif
