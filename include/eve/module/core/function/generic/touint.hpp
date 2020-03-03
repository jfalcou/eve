//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_TOUINT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_TOUINT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/convert.hpp>
#include <eve/detail/meta.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto touint_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return convert(a, as_<as_integer_t<value_type_t<T>, unsigned>>());
  }

  template<typename T, typename Tag>
  EVE_FORCEINLINE constexpr auto touint_(EVE_SUPPORTS(cpu_), Tag const& , T const &a) noexcept
  {
    return Tag()(convert)(a, as_<as_integer_t<value_type_t<T>, unsigned>>());
  }
}

#endif
