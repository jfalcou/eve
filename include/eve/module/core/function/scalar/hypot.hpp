//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/max.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  hypot_(EVE_SUPPORTS(cpu_)
        , T const &a0
        , T const &a1) noexcept
  requires(T, floating_point<T>)
  {
    return sqrt(fma(a0, a0, sqr(a1)));
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  hypot_(EVE_SUPPORTS(cpu_)
        , pedantic_type const &
        , T const &a0
        , T const &a1) noexcept
  requires(T, floating_point<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      if (is_infinite(a1)|| is_infinite(a0)) return Inf<T>();
    }
    if constexpr(std::is_same_v<T, float>)
    {
      return float(eve::hypot(double(a0), double(a1))); 
    }
    else
    {
      auto e = eve::max( exponent(a0), exponent(a1));
      e = eve::min(eve::max(e,Minexponent<T>()),Maxexponentm1<T>());
      T aa = pedantic_(ldexp)(a0, -e);
      T bb = pedantic_(ldexp)(a1, -e); 
      return eve::pedantic_(ldexp)( eve::sqrt(fma(aa, aa, sqr(bb))), e);
    }  
  }
}

#endif
