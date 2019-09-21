//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_TRUNC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_TRUNC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/abs.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/maxflint.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto trunc_(EVE_SUPPORTS(cpu_),
                                        T const &a0) noexcept requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return eve::abs(a0) < Maxflint<T>() ? raw_(trunc)(a0) : a0;
    else
      return a0;
  }

  // -----------------------------------------------------------------------------------------------
  // Raw case
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  trunc_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a0) noexcept requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return static_cast<T>(static_cast<as_integer_t<T>>(a0));
    else
      return a0;
  }
}

#endif
