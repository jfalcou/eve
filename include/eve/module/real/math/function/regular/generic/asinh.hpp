//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/branch.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/add.hpp>
#include <eve/function/average.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/log.hpp>
#include <eve/function/count_true.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/oneosqrteps.hpp>
#include <eve/constant/sqrteps.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto asinh_(EVE_SUPPORTS(cpu_)
                             , const T &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using vt_t = value_type_t<T>;
      T x =  eve::abs(a0);
      if constexpr(scalar_value<T>) if (x < sqrteps(eve::as<T>())) return a0; // scalar early return
      auto x_gt_oneosqrteps = x > oneosqrteps(eve::as<T>());
      auto  bts =  bitofsign(a0);
      if constexpr(std::is_same_v<vt_t, double>)
      {
        if constexpr(scalar_value<T>) // faster for great or small values
        {
          if (x_gt_oneosqrteps)         return bit_xor(log(x)+log_2(eve::as<T>()), bts);
          else if (x >= eve::half(eve::as<T>())) return bit_xor(log(x+hypot(one(eve::as<T>()), x)), bts);
        }
        // remaining scalar case and all simd cases to avoid multiple computations as
        // this one is always ok
        T z = if_else(x_gt_oneosqrteps,dec(x), x+sqr(x)/eve::inc(hypot(one(eve::as<T>()), x)));
        if constexpr(eve::platform::supports_infinites) z = if_else((x == inf(eve::as<T>())), x, z);
        z =  add[x_gt_oneosqrteps](eve::log1p(z), log_2(eve::as<T>()));
        return bit_xor(z, bts);
      }
      else if constexpr(std::is_same_v<vt_t, float>)
      {
        auto x_lt_half = x < half(eve::as<T>());
        T x2 = sqr(x);
        T z = zero(eve::as<T>());
        std::size_t nb = eve::count_true(x_lt_half);
        if(nb > 0)
        {
          z = horn<T, 0x3f800000, 0xbe2aa9ad, 0x3d9949b1, 0xbd2ee581, 0x3ca4d6e6> (x2)*x;
          if(nb >= cardinal_v<T>) return  bit_xor(z, bts);
        }
        auto case_1 = [](T const & x){return x; };                              // great x
        auto case_2 = [](T const & x){return average(x, hypot(one(eve::as<T>()), x)); }; // lesser x
        auto tmp =  branch<scalar_value<T>>(x_gt_oneosqrteps, case_1, case_2)(x);
        auto z1 = bit_xor(if_else(x_lt_half, z, log(tmp)+log_2(eve::as<T>())), bts);
        if constexpr(eve::platform::supports_invalids) return if_else(is_nan(a0), eve::allbits, z1);
        else                                           return z1;
      }
    }
    else
    {
      return apply_over(eve::asinh, a0);
    }
  }
}
