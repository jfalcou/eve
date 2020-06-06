//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log2.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/math/detail/generic/pow_kernel.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////
// some benches results                                       g++10     clang++10
// AVX2 FMA
// std_pow - float                                             22.7127   23.5926
// std_pow - double                                            137.553   137.081
// eve::pow_abs - eve::wide<float, eve::fixed<8l>, eve::avx_>  13.9966   14.1333
// eve::pow_abs - eve::wide<double, eve::fixed<4l>, eve::avx_> 156.477   62.6098
// eve::pow_abs - float                                        78.1466   94.3149
// eve::pow_abs - double                                       141.136   136.408

namespace eve::detail
{

  template<floating_real_value T, floating_real_value U>
  auto pow_abs_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pow_abs, a, b);
  }

  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t =  element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto ax = abs(a);
        auto tmp = exp2(convert(log2(convert(ax, double_))*convert(b, double_), single_));
        tmp =  if_else(is_eqz(b)||is_equal(a, One(as(a))), eve::one_, tmp);
        tmp =  if_else(is_eqz(b)&&is_eqz(a), eve::one_, tmp);
        tmp =  if_else(is_equal(a, One(as(a))), eve::one_, tmp);
        return tmp;
      }
      else  if constexpr(std::is_same_v<elt_t, double>)
      {
        auto std_pow_abs = []( auto const &a, auto const &b){return std::pow(abs(a), b); };
        return map(std_pow_abs, a, b);
       }
    }
    else
      return apply_over(pow_abs, a, b);
  }

  template<floating_real_scalar_value T>
  EVE_FORCEINLINE constexpr auto pow_abs_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr(std::is_same_v<elt_t, float>)
    {
      if(is_eqz(b)||is_equal(a, One(as(a)))) return One(as(a));
      if(is_eqz(b)&&is_eqz(a))               return One(as(a));
      if(is_equal(a, One(as(a))))            return One(as(a));
      auto ax = abs(a);
      auto tmp = exp2(convert(log2(convert(ax, double_))*convert(b, double_), single_));
      return tmp;
    }
    else  if constexpr(std::is_same_v<elt_t, double>)
    {
      return std::pow(abs(a), b);
    }
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(raw_(pow_abs), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), raw_type const &, T a, T b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return eve::exp2(b * eve::log2(eve::abs(a)));
    }
    else
      return apply_over(raw_(pow_abs), a, b);
  }

}
