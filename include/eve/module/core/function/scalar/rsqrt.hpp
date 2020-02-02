//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_RSQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/raw.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  rsqrt_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a0) noexcept
  requires(T,  floating_point<T>)
  {
    return eve::rec(eve::sqrt(a0));
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto rsqrt_(EVE_SUPPORTS(cpu_),
                                        T const &a0) noexcept
  requires(T,  floating_point<T>)
  {
    // needed as by sqrt IEEE requirements : sqrt(-0.0) is -0.0
    return a0 ? rec(eve::sqrt(a0)) : Inf(as(a0));
  }
  template<typename T>
  EVE_FORCEINLINE constexpr auto rsqrt_(EVE_SUPPORTS(cpu_)
                                       , pedantic_type const &
                                       , T const &a0) noexcept
  requires(T,  floating_point<T>)
  {
    return eve::rsqrt(a0); 
  }
}

#endif
