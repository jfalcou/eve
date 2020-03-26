//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FDIM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FDIM_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  fdim_(EVE_SUPPORTS(cpu_), T const &x, T const &y) noexcept
  requires std::floating_point<T>
  {
    if constexpr(eve::platform::supports_invalids)
      if (is_unordered(x, y)) return Nan(as(x)); 
    return x > y ? x-y : Zero(as(x)); 
  }
}

#endif
