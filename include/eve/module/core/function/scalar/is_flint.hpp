//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_FLINT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_FLINT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/frac.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  is_flint_(EVE_SUPPORTS(cpu_), T const &a) noexcept Requires(as_logical_t<T>, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return is_eqz(frac(a));
    else
      return true;
  }
}

#endif
