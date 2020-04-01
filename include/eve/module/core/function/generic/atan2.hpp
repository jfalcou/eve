//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ATAN2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ATAN2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/div.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/module/core/detail/generic/atan_kernel.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto atan2_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(atan2, a, b); 
  }

  template<floating_value T>
  EVE_FORCEINLINE auto atan2_( EVE_SUPPORTS(cpu_)
                                        , T const &a0
                                        , T const &a1
                                        ) noexcept
  
  {
    auto q = eve::abs(a0/a1);
    auto z = detail::atan_kernel(q, eve::rec(q));
    return if_else(is_positive(a1), z, (Pi(as(a0))-z))*signnz(a0);
  }

  // -----------------------------------------------------------------------------------------------
  // pedantic case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto atan2_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &   
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic_(atan2), a, b); 
  }
  
  template<floating_value T>
  EVE_FORCEINLINE auto atan2_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a0
                             , T const &a1
                             ) noexcept
  {
    if constexpr(scalar_value<T>  && platform::supports_nans)
    {
      if (is_unordered(a0, a1)) return Nan(as(a0));
    }
    T a00 = a0, a10 = a1;
    auto test1 =  eve::is_infinite(a0)&& eve::is_infinite(a1);
    if constexpr(platform::supports_infinites)
    {
      a00 =  eve::if_else(test1, eve::copysign(One(as(a0)), a00), a00);
      a10 =  eve::if_else(test1, eve::copysign(One(as(a0)), a10), a10);
    }
    
    T q = eve::abs(a00/a10);
    T z = atan_kernel(q, rec(q));
    T sgn = signnz(a0);
    if constexpr(scalar_value<T>)
    {
      z = (is_positive(a10)? z: Pi<T>()-z)*sgn;
      return is_eqz(a00) ? if_else(is_negative(a10), Pi(as(a00))*sgn, eve::zero_) : z;
    }
    else
    {
      z = eve::if_else(eve::is_positive(a10), z, eve::Pi(as(a0))-z)*sgn;
      z = eve::if_else( eve::is_eqz(a00),
                        eve::if_else( eve::is_negative(a10),  eve::Pi(as(a0))*sgn, eve::zero_),
                        z);
      if constexpr(platform::supports_nans) return  eve::if_else( is_unordered(a00, a10), eve::allbits_, z);
      else                                  return z;
    }
  }
}

#endif
