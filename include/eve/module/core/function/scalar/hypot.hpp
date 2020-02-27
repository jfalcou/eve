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
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  hypot_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  requires(T, floating_point<T>)
  {
    return sqrt(fma(a0, a0, sqr(a1)));
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  hypot_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1, T const &a2) noexcept
  requires(T, floating_point<T>)
  {
    return sqrt(fma(a0, a0, fma(a1, a1, sqr(a2))));
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  hypot_(EVE_SUPPORTS(cpu_)
        ,  pedantic_type const &
        , T const &a0
        , T const &a1) noexcept
  requires(T, floating_point<T>)
  {
    using i_t = as_integer_t<T>;
    if constexpr(eve::platform::supports_invalids)
    {
      if (is_infinite(a1) || is_infinite(a0)) return Inf<T>();
    }
    auto r =  eve::abs(a0);
    auto i =  eve::abs(a1);
    if (is_eqz(r)) return i;
    if (is_eqz(i)) return r;
    if constexpr(std::is_same_v<T, float>)
    {
      return hypot(double(a0), double(a1)); 
    }
    else
    {
      i_t e =  exponent(eve::max(i, r));
      e = eve::min(eve::max(e,Minexponent<T>()),Maxexponentm1<T>());
      auto tmpr = pedantic_(ldexp)(r, -e);
      auto tmpi= pedantic_(ldexp)(i, -e); 
      return pedantic_(ldexp)(eve::sqrt(fma(tmpi, tmpi, sqr(tmpr))), e);   
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  hypot_(EVE_SUPPORTS(cpu_)
        ,  pedantic_type const &
        , T const &a0
        , T const &a1
        , T const &a2 ) noexcept
  requires(T, floating_point<T>)
  {
    using i_t = as_integer_t<T>;
    if constexpr(eve::platform::supports_invalids)
    {
      if (is_infinite(a2) || is_infinite(a1) || is_infinite(a0)) return Inf<T>();
    }
    auto r =  eve::abs(a0);
    auto i =  eve::abs(a1);
    auto j =  eve::abs(a2);
    if (is_eqz(r)) return pedantic_(hypot)(a1, a2);
    if (is_eqz(i)) return pedantic_(hypot)(a0, a2);
    if (is_eqz(j)) return pedantic_(hypot)(a0, a1); 
    if constexpr(std::is_same_v<T, float>)
    {
      return hypot(double(a0), double(a1), double(a2)); 
    } 
    else
    {
      i_t e =  exponent(eve::max(eve::max(i, r), j));
      e = eve::min(eve::max(e,Minexponent<T>()),Maxexponentm1<T>());
      auto tmpr = pedantic_(ldexp)(r, -e);
      auto tmpi = pedantic_(ldexp)(i, -e);
      auto tmpj = pedantic_(ldexp)(j, -e);      
      return pedantic_(ldexp)(eve::sqrt(fma(tmpr, tmpr, fma(tmpi, tmpi, sqr(tmpj)))), e);   
    }
  }   
}

#endif
