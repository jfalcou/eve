//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FNMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FNMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/fms.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  fnms_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c) noexcept
  requires(T, vectorizable<T>)
  {
    return -a * b - c;
  }
 
  template<typename D, typename T>
  EVE_FORCEINLINE constexpr auto
  fnms_(EVE_SUPPORTS(cpu_)
      , D const & 
      , T const &a, T const &b, T const &c) noexcept
  requires(T, vectorizable<T>)
  {
    return -D()(fma)(a, b, c);
  }
}

#endif
