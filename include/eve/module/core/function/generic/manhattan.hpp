//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_MANHATTAN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_MANHATTAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/min.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto manhattan_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(manhattan, a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto manhattan_( EVE_SUPPORTS(cpu_)
                             , T const &a
                             , T const &b
                             ) noexcept

  {
    if constexpr(native<T>) return eve::abs(a)+eve::abs(b);
    else                    return  apply_over(manhattan, a, b);
  }

  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto manhattan_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b
                              , V const &c) noexcept
  requires compatible_values<T, U> &&  compatible_values<T, V>
  {
    return arithmetic_call(manhattan, a, b, c);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto manhattan_( EVE_SUPPORTS(cpu_)
                             , T const &a
                             , T const &b
                             , T const &c
                             ) noexcept

  {
    if constexpr(native<T>) return  eve::abs(a)+eve::abs(b)+eve::abs(c);
    else                    return  apply_over(manhattan, a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // pedantic case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto manhattan_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic_(manhattan), a, b);
  }
  template<floating_value T>
  EVE_FORCEINLINE auto manhattan_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             ) noexcept
  requires native<T>
  {
    const auto inf = Inf(as(a));
    auto aa = eve::abs(a);
    auto infa = aa == inf;
    if constexpr(scalar_value<T>) { if (infa) return inf;}
    auto bb = eve::abs(b);
    auto infb = bb == inf;
    if constexpr(scalar_value<T>) { if (infb) return inf; }
    auto r =  eve::abs(a)+eve::abs(b);
    if constexpr(scalar_value<T>) { return r; }
    else { return if_else(infa || infb ,  inf, r); }
  }

  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto manhattan_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                              , T const &a
                              , U const &b
                              , V const &c) noexcept
  requires compatible_values<T, U> &&  compatible_values<T, V>
  {
    return arithmetic_call(manhattan, a, b, c);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto manhattan_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             , T const &c
                             ) noexcept
  requires native<T>
  {
    const auto inf = Inf(as(a));
     auto aa = eve::abs(a);
    auto infa = aa == inf;
    if constexpr(scalar_value<T>) { if (infa) return inf;}
    auto bb = eve::abs(b);
    auto infb = bb == inf;
    if constexpr(scalar_value<T>) { if (infb) return inf; }
    auto cc = eve::abs(c);
    auto infc = cc == inf;
    if constexpr(scalar_value<T>) { if (infc) return inf; }
    auto r =  eve::abs(a)+eve::abs(b)+eve::abs(c);
    if constexpr(scalar_value<T>) { return r; }
    else { return if_else(infa || infb || infc,  inf, r); }
  }

}

#endif
