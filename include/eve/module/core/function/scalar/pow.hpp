//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_POW_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_POW_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>  
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  pow_(EVE_SUPPORTS(cpu_)
          , T const &a0, T const &a1) noexcept
  requires std::floating_point<T>
  {
    auto ltza0 = is_ltz(a0);
    auto isinfa1 = is_infinite(a1);
    if( a0 == Mone<T>() && isinfa1 ) return One<T>();
    if( ltza0 && !is_flint(a1) && !is_infinite(a1) ) return Nan<T>();
    auto z = pow_abs(a0, a1);
    if (isinfa1) return z;
    return (is_negative(a0) && is_odd(a1)) ? -z : z;
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  pow_(EVE_SUPPORTS(cpu_)
      , T const &a0, U const &a1) noexcept
  Requires(T, floating_point<T>, integral<U>)
  {
    if constexpr(std::is_unsigned_v<U>)
    {
      T base = a0;
      U expo = a1;
      
      T result(1); 
      while(expo)
      {
        if(is_odd(expo)) result *= base;
        expo >>= 1;
        base = sqr(base);
      }
      return result;
    }
    else 
    {
      using u_t =  as_integer_t<U, unsigned>;
      T tmp = pow(a0, u_t(eve::abs(a1)));
      return if_else (a1 < 0,  rec(tmp),  tmp); 
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  pow_(EVE_SUPPORTS(cpu_)
      , T a0, U a1) noexcept
  Requires(T, integral<T>, integral<U>)
  {
    if (a0 == 1) return 1;  
    if ((a1 >= U((sizeof(T)*8-1-std::is_signed_v<T>))) || a1 < 0) return 0; 
    constexpr uint8_t highest_bit_set[] = {
      0, 1, 2, 2, 3, 3, 3, 3,
      4, 4, 4, 4, 4, 4, 4, 4,
      5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5,
      6, 6, 6, 6, 6, 6, 6, 6,
      6, 6, 6, 6, 6, 6, 6, 6,
      6, 6, 6, 6, 6, 6, 6, 6,
      6, 6, 6, 6, 6, 6, 6}; // anything past 63 is a guaranteed overflow with base > 1

    T result = 1;
    switch (highest_bit_set[a1]) {
    case 6:
        if (a1 & 1) result *= a0;
        a1 >>= 1;
        a0 *= a0;
    case 5:
        if (a1 & 1) result *= a0;
        a1 >>= 1;
        a0 *= a0;
    case 4:
        if (a1 & 1) result *= a0;
        a1 >>= 1;
        a0 *= a0;
    case 3:
        if (a1 & 1) result *= a0;
        a1 >>= 1;
        a0 *= a0;
    case 2:
        if (a1 & 1) result *= a0;
        a1 >>= 1;
        a0 *= a0;
    case 1:
        if (a1 & 1) result *= a0;
    default:
        return result;
    }
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  pow_(EVE_SUPPORTS(cpu_)
      , raw_type const &
      , T const &a0, T const &a1) noexcept
  requires std::floating_point<T>
  {
    return exp(a1*log(a0)); 
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  pow_(EVE_SUPPORTS(cpu_)
      , raw_type const &
      , T const &a0, U const &a1) noexcept
  Requires(T, Vectorizable<T>, integral<U>)
  {
    return pow(a0, a1); 
  }

}

#endif
